#include "MessageHandler.h"
#include "XmlSchemaValidator.h"

#include <QCommandLineParser>
#include <QCoreApplication>
#include <QDir>

void setupCommandLineParser(QCommandLineParser& parser);

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("XmlSchemaValidator");
    QCoreApplication::setApplicationVersion("0.1");

    QCommandLineParser parser;
    setupCommandLineParser(parser);
    parser.process(app);

    auto args = parser.positionalArguments();
    if (args.size() < 2)
        return -1;

    auto schemaFile = args.takeFirst();
    schemaFile = QDir::toNativeSeparators(schemaFile);

    XSV::MessageHandler messageHandler;
    XSV::XmlSchemaValidator validator{QUrl::fromLocalFile(schemaFile), &messageHandler};
    QStringList messages;
    QObject::connect(&messageHandler, &XSV::MessageHandler::msg,
        [&messages](QtMsgType type, const QString& msg)
        {
            messages.push_back(msg);
        });

    int failureCount = 0;
    for (const auto& arg : args)
    {
        qDebug("Validating XML file '%s'...", qPrintable(arg));
        auto result = validator.validate(arg);
        if (result)
        {
            qDebug("%s is valid.", qPrintable(arg));
        }
        else
        {
            qDebug("***%s is invalid.", qPrintable(arg));
            failureCount++;
        }

        if (!messages.empty())
            qDebug(qPrintable(messages.join("\n")));

        qDebug("----------------------");
    }

    return failureCount;
}

void setupCommandLineParser(QCommandLineParser& parser)
{
    parser.setApplicationDescription("Command line tool to validate 1-n XML files against a given schema.");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("schemaFile", "The path to the schema file.");
    parser.addPositionalArgument("xmlFile", "The path to an .xml file");
}

