#ifndef THREADCOM_H
#define THREADCOM_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <QSerialPort>

class ThreadCOM : public QThread
{
    Q_OBJECT

public:
    explicit ThreadCOM(QObject *parent = nullptr);
    ~ThreadCOM();

    void transaction(const QString &portName, int waitTimeout, const QString &request);

signals:
    void response(const QString &s);
    void error(const QString s);
    void timeout(const QString s);

public:
    QSerialPort *serial;

private:
    void run() override;

    QString m_portName;
    QString m_request;
    int m_waitTimeout = 0;
    QMutex m_mutex;
    QWaitCondition m_cond;
    bool m_quit = false;
};
//! [0]

#endif // MASTERTHREAD_H
