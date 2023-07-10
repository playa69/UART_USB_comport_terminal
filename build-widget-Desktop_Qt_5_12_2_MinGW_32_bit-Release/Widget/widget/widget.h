#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QMutex>
#include <QThread>
#include <QWaitCondition>

#include <QTimer>
#include <QTime>

#include <QLCDNumber>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


    // слоты (event_handlers)
private slots:
    void on_pushButton_2_clicked();
    void receiveMessage();
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    //void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

    //quint16 ModBusCRC16(uchar *p, quint16 n);


    // сигналы
signals:
    void error(const QString s);

// переменнные
private:
    Ui::Widget *ui;
    QTimer *tmr;
    QSerialPort serialPort;
    QSerialPortInfo info;
    QString buffer;
    QString code;
    QString x;
    QString y;
    QString x_0;
    QString y_0;
    QString hs;
    int codeSize;
    int after_hex1;
    int after_hex2;
    int after_hex3;
    int after_hex4;
    int after_hex5;
    int after_hex_wo_hs;
    int delta_x;
    int delta_y;
    int x1;
    int x2;
    int x3;
    int x4;
    int x5;
    int x6;
    int x7;
    int x8;
    int arr[8];
    bool ok;
};

// класс таймер чтобы функцию слип
class Sleeper : public QThread
{
public:
    static void usleep(unsigned long usecs){
        QThread::usleep(usecs);
    }
    static void msleep(unsigned long msecs){
        QThread::msleep(msecs);
    }
    static void sleep(unsigned long secs){
        QThread::sleep(secs);}
};

#endif // WIDGET_H
