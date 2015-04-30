#ifndef XMLSCHEMAVALIDATOR_H
#define XMLSCHEMAVALIDATOR_H

#include <QUrl>

class QAbstractMessageHandler;

namespace XSV
{

class XmlSchemaValidator
{
public:
    explicit XmlSchemaValidator(QAbstractMessageHandler* messageHandler = nullptr);
    explicit XmlSchemaValidator(QUrl schemaFile, QAbstractMessageHandler* messageHandler = nullptr);

    void setSchemaFile(QUrl schemaFile) { m_schemaFile = std::move(schemaFile); }
    void setDisableMessageHandler(bool disable) { m_disableMessageHandler = disable; }
    void setMessageHandler(QAbstractMessageHandler* messageHandler) { m_messageHandler = messageHandler; }

    bool validate(const QString& xmlFilePath) const;

private:
    /*!
     * \brief Returns a path that does not contain the "qrc" prefix used for Qt's resource system.
     * \note This can be necessary in case the same path should be used as an argument to e.g. a
             QFile and a QUrl. QFile does not work with a "qrc", QUrl however does not work without...
     */
    QString pathWithoutQrcPrefix(const QString& path) const;

    bool m_disableMessageHandler;
    QAbstractMessageHandler* m_messageHandler;
    QUrl m_schemaFile;
};

}

#endif // XMLSCHEMAVALIDATOR_H
