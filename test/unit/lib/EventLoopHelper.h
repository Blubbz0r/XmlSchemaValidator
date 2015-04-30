#ifndef EVENTLOOPHELPER_H
#define EVENTLOOPHELPER_H

#include <QObject>

/*!
 * \brief Helper class that allows to run an event loop while still being able to automatically execute the tests from gtest.

          Example usage:
          \code
          int result;
          EventLoopHelper eventLoopHelper;
          QObject::connect(&eventLoopHelper, &EventLoopHelper::finished, &app, QCoreApplication::quit);
          QTimer::singleShot(0, [&result, &eventLoopHelper]{ eventLoopHelper.run(result); });
          app.exec();
          return result;
          \endcode
 */
class EventLoopHelper : public QObject
{
    Q_OBJECT

public slots:
    void run(int& result);

signals:
    void finished();
};

#endif // EVENTLOOPHELPER_H
