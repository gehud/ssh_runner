#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>

#include "config.hpp"
#include "cmd.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName(PROJECT_NAME);
    QCoreApplication::setApplicationVersion(PROJECT_VERSION);

    QCommandLineParser parser;
    parser.setApplicationDescription("SSH Command Runner. Executes commands on remote devices.");
    parser.addVersionOption();

    QCommandLineOption helpOption(QStringList() << "h" << "help",
                                  "Displays help on commandline options.");

    parser.addOption(helpOption);

    QCommandLineOption inputOption(QStringList() << "i" << "input",
                                   "Input file with device IP addresses.",
                                   "input_file");
    parser.addOption(inputOption);

    QCommandLineOption userOption(QStringList() << "u" << "user",
                                  "Username for authentication.",
                                  "username");
    parser.addOption(userOption);

    QCommandLineOption passwordOption(QStringList() << "p" << "password",
                                      "Password for authentication.",
                                      "password");
    parser.addOption(passwordOption);

    QCommandLineOption outputOption(QStringList() << "o" << "output",
                                    "Output JSON file.",
                                    "output_file");
    parser.addOption(outputOption);

    parser.process(app);

    if (parser.isSet(helpOption))
    {
        parser.showHelp(EXIT_SUCCESS);
        return EXIT_SUCCESS;
    }

    if (!parser.isSet(inputOption))
    {
        qCritical() << "Error: --input argument is required";
        parser.showHelp(EXIT_FAILURE);
        return EXIT_FAILURE;
    }

    if (!parser.isSet(userOption))
    {
        qCritical() << "Error: --user argument is required";
        parser.showHelp(EXIT_FAILURE);
        return EXIT_FAILURE;
    }

    if (!parser.isSet(passwordOption))
    {
        qCritical() << "Error: --password argument is required";
        parser.showHelp(EXIT_FAILURE);
        return EXIT_FAILURE;
    }

    if (!parser.isSet(outputOption))
    {
        qCritical() << "Error: --output argument is required";
        parser.showHelp(EXIT_FAILURE);
        return EXIT_FAILURE;
    }

    QString inputFile = parser.value(inputOption);
    QString username = parser.value(userOption);
    QString password = parser.value(passwordOption);
    QString outputFile = parser.value(outputOption);

    CommandRunner runner;

    if (!runner.readDevicesFromFile(inputFile)) {
        return EXIT_FAILURE;
    }

    if (!runner.saveResultsToFile(outputFile)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
