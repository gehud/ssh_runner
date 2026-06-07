#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>

#include "config.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName(PROJECT_NAME);
    QCoreApplication::setApplicationVersion(PROJECT_VERSION);

    return EXIT_SUCCESS;
}
