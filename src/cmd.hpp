#pragma once

#include <QString>
#include <QList>
#include <QJsonObject>

class CommandRunner
{
public:
    CommandRunner();

    bool readDevicesFromFile(const QString &filename);
    bool saveResultsToFile(const QString &filename);

private:
    QList<QString> _devices;
    QJsonObject _results;
};