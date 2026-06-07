#include "ssh.hpp"

#include <QDebug>
#include <QProcess>

SshClient::SshClient(QObject *parent) : QObject(parent)
{
}

SshClient::Result SshClient::run(const QString &ip,
                                 const QString &username)
{
    Result result;

    QProcess process;
    QString target = QString("%1@%2").arg(username).arg(ip);
    QStringList args = {
        "-o", "ConnectTimeout=5",
        "-o", "PasswordAuthentication=no",
        target,
        "/tmp/test_app"};

    process.start("ssh", args);

    if (!process.waitForStarted(5000))
    {
        qCritical() << "Failed to start SSH process: " << process.errorString();
        result.success = false;
        result.error = process.errorString();
        return result;
    }

    if (!process.waitForFinished(-1))
    {
        qCritical() << "Failed to finish SSH process: " << process.errorString();
        process.kill();
        result.success = false;
        result.error = process.errorString();
        return result;
    }

    int exitCode = process.exitCode();

    result.output = QString(process.readAllStandardOutput());
    if (exitCode == 0 && !result.output.isEmpty())
    {
        result.success = true;
        return result;
    }

    result.success = false;

    if (exitCode == 0 && result.output.isEmpty())
    {
        result.error = "empty output";
    }
    else
    {
        QString errorOutput = process.readAllStandardError();

        switch (exitCode)
        {
        case 127:
            result.error = "missing file";
            break;
        default:
            if (errorOutput.contains("Permission denied"))
            {
                result.error = "authentication failed";
            }
            else if (errorOutput.contains("Connection timed out"))
            {
                result.error = "timeout";
            }
            else
            {
                result.error = errorOutput;
            }
        }
    }

    return result;
}