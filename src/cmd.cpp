#include "cmd.hpp"

#include <QFile>

CommandRunner::CommandRunner()
{
}

bool CommandRunner::readDevicesFromFile(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qCritical() << "Failed to open input file:" << filename;
        return false;
    }

    _devices.clear();
    QTextStream stream(&file);

    while (!stream.atEnd())
    {
        QString line = stream.readLine().trimmed();
        if (!line.isEmpty())
        {
            _devices.append(line);
        }
    }

    file.close();

    if (_devices.isEmpty())
    {
        qCritical() << "No devices found in input file";
        return false;
    }

    qDebug() << "Loaded" << _devices.size() << "devices from file";
    return true;
}

QJsonObject CommandRunner::runOnDevice(const QString &ip, const QString &username)
{
    SshClient::Result result = _client.run(ip, username);

    QJsonObject obj;
    obj["ok"] = result.success;

    if (result.success)
    {
        obj["output"] = result.output;
    }
    else
    {
        obj["error"] = result.error;
    }

    return obj;
}

void CommandRunner::run(const QString &username)
{
    _results = QJsonObject();

    for (const QString &ip : _devices)
    {
        qDebug() << "Processing device:" << ip;
        QJsonObject deviceResult = runOnDevice(ip, username);
        _results[ip] = deviceResult;
    }
}

bool CommandRunner::saveResultsToFile(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly))
    {
        qCritical() << "Failed to create output file:" << filename;
        return false;
    }

    QJsonDocument doc(_results);
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();

    qDebug() << "Results saved to" << filename;
    return true;
}