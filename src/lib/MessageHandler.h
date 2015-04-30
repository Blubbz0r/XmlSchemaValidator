#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <QAbstractMessageHandler>

namespace XSV
{

class MessageHandler : public QAbstractMessageHandler
{
    Q_OBJECT

public:
    MessageHandler(QObject* parent = nullptr);

signals:
    void msg(QtMsgType type, const QString& msg);

protected:
    void handleMessage(QtMsgType type, const QString& description, const QUrl& identifier,
                       const QSourceLocation& sourceLocation) override;

private:
    QString plainDescription(const QString& description) const;
};

}

#endif // MESSAGEHANDLER_H
