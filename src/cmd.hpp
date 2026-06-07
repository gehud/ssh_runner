#pragma once

#include <QString>
#include <QList>
#include <QJsonObject>

#include "ssh.hpp"

class CommandRunner
{
public:
    CommandRunner();

    bool readDevicesFromFile(const QString &filename);
    bool saveResultsToFile(const QString &filename);
    void run(const QString& username);

private:
    QList<QString> _devices;
    QJsonObject _results;
    SshClient _client;

    QJsonObject runOnDevice(const QString& ip, const QString& username);
};