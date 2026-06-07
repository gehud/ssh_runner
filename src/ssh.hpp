#pragma once

#include <QString>
#include <QObject>

class SshClient : public QObject
{
public:
    explicit SshClient(QObject *parent = nullptr);

    struct Result
    {
        bool success;
        QString output;
        QString error;
    };

    Result run(const QString &ip, const QString &username);
};
