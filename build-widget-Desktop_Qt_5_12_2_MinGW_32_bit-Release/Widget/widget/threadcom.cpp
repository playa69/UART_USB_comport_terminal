#include "threadcom.h"

#include <QTime>

ThreadCOM::ThreadCOM(QObject *parent) :
    QThread(parent)
{
}

ThreadCOM::~ThreadCOM()
{
    m_mutex.lock();
    m_quit = true;
    m_cond.wakeOne();
    m_mutex.unlock();
    wait();
}

void ThreadCOM::transaction(const QString &portName, int waitTimeout, const QString &request)
{
//! [1]
    const QMutexLocker locker(&m_mutex);
    m_portName = portName;
    m_waitTimeout = waitTimeout;
    m_request = request;
//! [3]
    if (!isRunning())
        start();
    else
        m_cond.wakeOne();
}

void ThreadCOM::run()
{
    int currentWaitTimeout = m_waitTimeout;
    QString currentRequest = m_request;

    if (m_portName.isEmpty()) {
        emit error(tr("No port name specified"));
        return;
    }

    serial = new QSerialPort(this);
    serial->close();
    serial->setPortName(m_portName);

    if (!serial->open(QIODevice::ReadWrite)) {
        emit error(tr("Can't open %1, error code %2").arg(m_portName).arg(serial->error()));
            return;
    }

    while (!m_quit)
    {
        const QByteArray requestData = currentRequest.toUtf8();
        serial->write(requestData);
        if (serial->waitForBytesWritten(0)) {
            if (serial->waitForReadyRead(10)) {
                QByteArray responseData = serial->read(64);
//                while (serial.waitForReadyRead(10))
//                    responseData += serial.readAll();

                const QString response = QString::fromUtf8(responseData);
                emit this->response(response);
            } else {
                emit timeout(tr("Wait read response timeout %1")
                             .arg(QTime::currentTime().toString()));
            }
        } else {
            emit timeout(tr("Wait write request timeout %1")
                         .arg(QTime::currentTime().toString()));
        }

        usleep(50);
    }  // while(!m_quit)
}
