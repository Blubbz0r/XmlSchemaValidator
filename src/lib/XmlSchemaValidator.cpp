#include "XmlSchemaValidator.h"

#include <QFile>
#include <QXmlSchema>
#include <QXmlSchemaValidator>

namespace XSV
{

XmlSchemaValidator::XmlSchemaValidator(QAbstractMessageHandler* messageHandler)
    : XmlSchemaValidator(QUrl(), messageHandler)
{
}

XmlSchemaValidator::XmlSchemaValidator(QUrl schemaFile, QAbstractMessageHandler* messageHandler)
    : m_schemaFile(std::move(schemaFile)),
      m_disableMessageHandler(false),
      m_messageHandler(messageHandler)
{
}

bool XmlSchemaValidator::validate(const QString& xmlFilePath) const
{
    if (m_schemaFile.isEmpty())
        throw std::logic_error("Need a valid schema file path to validate xml file " + xmlFilePath.toStdString());

    QXmlSchema xmlSchema;
    xmlSchema.load(m_schemaFile);
    if (!xmlSchema.isValid())
        return false;

    QFile xmlFile(pathWithoutQrcPrefix(xmlFilePath));
    if (!xmlFile.open(QIODevice::ReadOnly))
        return false;

    QXmlSchemaValidator validator(xmlSchema);
    if (!m_disableMessageHandler && m_messageHandler)
        validator.setMessageHandler(m_messageHandler);

    return validator.validate(&xmlFile, QUrl(xmlFilePath));
}

QString XmlSchemaValidator::pathWithoutQrcPrefix(const QString& path) const
{
    auto qrcPrefix = QStringLiteral("qrc");
    if (!path.startsWith(qrcPrefix))
        return path;

    return path.mid(qrcPrefix.size(), path.size() - qrcPrefix.size());
}

}
