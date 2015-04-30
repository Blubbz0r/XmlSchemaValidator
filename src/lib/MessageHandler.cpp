#include "messagehandler.h"

#include <QFile>
#include <QTextStream>
#include <QXmlStreamReader>

namespace XSV
{

QFile file;

MessageHandler::MessageHandler(QObject* parent) : QAbstractMessageHandler(parent)
{
}

void MessageHandler::handleMessage(QtMsgType type, const QString& description,
                                   const QUrl& identifier, const QSourceLocation& sourceLocation)
{
    if (!file.isOpen())
    {
        file.setFileName("C:/test/out.txt");
        file.open(QIODevice::WriteOnly | QIODevice::Text);
    }

    static QTextStream out(&file);
    auto plainDescription = this->plainDescription(description);
    const bool hasLine = sourceLocation.line() != -1; // TODO: only add line to message when this is true..
    switch (type)
    {
    case QtWarningMsg:
        out << QStringLiteral("Warning in %1, at line %2, column %3: %4")
                   .arg(sourceLocation.uri().toString(), QString::number(sourceLocation.line()),
                        QString::number(sourceLocation.column()), plainDescription);
        break;
    case QtFatalMsg:
    {
        const auto errorCode(identifier.fragment());
        QUrl uri(identifier);
        uri.setFragment(QString());

        auto location = sourceLocation.isNull() ? "Unknown location"
                                                : sourceLocation.uri().toString();
        auto errorId = (uri.toString() == QLatin1String("http://www.w3.org/2005/xqt-errors"))
                           ? errorCode
                           : identifier.toString();

        out << QStringLiteral("Error %1 in %2, at line %3, column %4: %5")
                   .arg(errorId, location, QString::number(sourceLocation.line()),
                        QString::number(sourceLocation.column()), plainDescription);
        break;
    }
    }

    emit msg(type, plainDescription);
}

QString MessageHandler::plainDescription(const QString& description) const
{
    QXmlStreamReader reader(description);
    QString result;
    result.reserve(description.size());

    while (!reader.atEnd())
    {
        reader.readNext();

        switch (reader.tokenType())
        {
        case QXmlStreamReader::Characters:
            result.append(reader.text().toString());
            break;
        default:
            break;
        }
    }

    return result;
}

}
