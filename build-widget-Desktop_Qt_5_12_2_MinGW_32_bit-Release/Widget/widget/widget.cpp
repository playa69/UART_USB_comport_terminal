

#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QString>


int ModBusCRC16( int* p,
    unsigned short n)
{

    int w, i;
    unsigned char j;

    for (w = 0xFFFF, i = 0; i < n; i++)
    {
        w ^= p[i];
        for (j = 0; j < 8; j++) if (w & 1)
        {
                w >>= 1;
                w ^= 0xA001;
        }
            else w >>= 1;

    }
    return w;
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // Disable maximizing - фиксируем высоту и ширину окна
    setFixedSize(width(), height());

    // Adding title for widget - название проги
    QWidget::setWindowTitle("Terminal v1.0");

    /*
    // Baud Rate Ratios
    QList<qint32> baudRates = info.standardBaudRates(); // What baudrates does my computer support ?
    QList<QString> stringBaudRates;
    for(int i = 0 ; i < baudRates.size() ; i++){
        stringBaudRates.append(QString::number(baudRates.at(i)));
    }
    ui->comboBox_2->addItems(stringBaudRates);
    */
}
//это деструктор прочитай че он делает
Widget::~Widget()
{
    serialPort.close();
    delete ui;
}


void Widget::on_pushButton_2_clicked()
{


    //чекаем все доступные ком порты и подрубаемся к тому, кого зовут COM5 или к тому, кого сделали
    //ребята из силикон лабс
    QList<QSerialPortInfo> ports = info.availablePorts();
    QList<QString> stringPorts;
    int numb = 0;
    for(int i = 0 ; i < ports.size() ; i++){
        stringPorts.append(ports.at(i).portName());
        //ui->textBrowser->append(ports.at(i).manufacturer());
        if(ports.at(i).manufacturer() == "Silicon Labs")
        //if(ports.at(i).portName()== "COM5")
           numb = i;
    }
    serialPort.setPortName(ports.at(numb).portName());
    //ui->textBrowser->append(ports.at(numb).portName());

    //QString portName = ui->comboBox->currentText();

    if(!serialPort.open(QIODevice::ReadWrite)){ //Проблема тут
        ui->textBrowser->setTextColor(Qt::red);
        ui->textBrowser->append("Не могу open(QIODevice::ReadWrite)");

    }

   /* if (!serialPort.open(QIODevice::ReadWrite)) {
        emit error(tr("Can't open %1, error code %2").arg(portName).arg(serialPort.error()));
            return;
    }   */


        //проверка на вторую проблему

    if(!serialPort.isOpen()){
        ui->textBrowser->setTextColor(Qt::red);
        ui->textBrowser->append("Проблема с serialPort.isOpen()");
    }
    else {  

        //Defaultные параметры компорта
        //serialPort.setBaudRate(QSerialPort::Baud115200);
        serialPort.setBaudRate(QSerialPort::Baud9600);
        serialPort.setDataBits(QSerialPort::Data8);
        serialPort.setStopBits(QSerialPort::OneStop);
        serialPort.setParity(QSerialPort::NoParity);
        serialPort.setFlowControl(QSerialPort::NoFlowControl);


        //code = ui->lineEdit->text();
        //codeSize = code.size();

        // Коннектимся к receiveMessage чтобы у нас все работало
        connect(&serialPort,SIGNAL(readyRead()),this,SLOT(receiveMessage()));


    }


    tmr = new QTimer(this); // Создаем объект класса QTimer и передаем адрес переменной
    tmr->setInterval(500); // Задаем интервал таймера
    connect(tmr, SIGNAL(timeout()), this, SLOT(receiveMessage())); // Подключаем сигнал таймера к нашему слоту
    tmr->start(); // Запускаем таймер


}

/*
Одно из решений проблемы функции readAll() и read() это все вставлять в буфер и искать по кодовой
последовательности в конце каждого сообщения. далее удаляем само сообщение с кодом и выкидываем
его в терминал.

Посмотри буффер с кодом
нужно вернуть некоторые кнопки для их работы
ссылка в гитхабе
*/
static int ij = 0;

void Widget::receiveMessage()
{ 


    QByteArray dataBA;
    //Sleeper::msleep(100);
    //Sleeper::msleep(500);
    dataBA = serialPort.readAll();



    /*  буффер с кодом
     * норм вариант но в конце каждого сообщения нужен код который мы будем искать!
    QString data(dataBA.toHex()); // cast QByteArray to QString
    buffer.append(data);
    int index = buffer.indexOf(code);
    if(index != -1){
       QString message = buffer.mid(0,index);
       ui->textBrowser->setTextColor(Qt::blue);
       ui->textBrowser->append(message);
       buffer.remove(0,index+codeSize);
    }
    */


    /* просто выбрасываем всю информацию что получаем (один пакет разрывает на несколько и выкидывает
     * произвольно, поэтому это плохой вариант
    QByteArray dataBA = serialPort.readAll();
    ui->textBrowser->setTextColor(Qt::red);
    ui->textBrowser->append(dataBA.toHex());
    */


    QString data(dataBA.toHex());
    buffer.append(data);

    //int index = buffer.indexOf(code);

    if(buffer.length() > 19){

       QString message = buffer.mid(0,20);


       //STRING
       // можно юзать >>8, но я сделал так чтобы получить из пакета нужные переменные
       //в нужном типе данных
       x = buffer.mid(2,2) + buffer.mid(0,2);
       y = buffer.mid(6,2) + buffer.mid(4,2);
       x_0 = buffer.mid(10,2) + buffer.mid(8,2);
       y_0 = buffer.mid(14,2) + buffer.mid(12,2);
       hs = buffer.mid(18,2) + buffer.mid(16,2);

       QString after = x +" " + y +" " + x_0 + " " + y_0 + " " + hs;

       //integers
       // если хочешь посмотреть что что выводится юзай  ui->textBrowser->append(Qstring + QString::number( число ))
       after_hex1 = after.split(" ")[0].toInt(&ok,16);
       after_hex2 = after.split(" ")[1].toInt(&ok,16);
       after_hex3 = after.split(" ")[2].toInt(&ok,16);
       after_hex4 = after.split(" ")[3].toInt(&ok,16);
       after_hex5 = after.split(" ")[4].toInt(&ok,16); 

       //integers
       x1 = buffer.mid(0,2).toInt(&ok,16);
       x2 = buffer.mid(2,2).toInt(&ok,16);
       x3 = buffer.mid(4,2).toInt(&ok,16);
       x4 = buffer.mid(6,2).toInt(&ok,16);
       x5 = buffer.mid(8,2).toInt(&ok,16);
       x6 = buffer.mid(10,2).toInt(&ok,16);
       x7 = buffer.mid(12,2).toInt(&ok,16);
       x8 = buffer.mid(14,2).toInt(&ok,16);

       int y_0_10 = y_0.toInt(&ok, 16);
       int x_0_10 = x_0.toInt(&ok, 16);
        // нужен массив для работы функции ModBusCRC16
       arr[0] = x1; arr[1] = x2;
       arr[2] = x3; arr[3] = x4; arr[4] = x5;
       arr[5] = x6; arr[6] = x7; arr[7] = x8;

       int MBCRC16 = ModBusCRC16(arr, 8);

       //integers
       delta_x = after_hex1 - after_hex3;
       delta_y = after_hex2 - after_hex4;

       QString x_s = QString::number(delta_x,10); //delta x
       QString y_s = QString::number(delta_y,10); //delta y
       QString x_0_st = QString::number(x_0_10); // x 0
       QString y_0_st = QString::number(y_0_10); // y 0

       /*
       // ---------------------------------------------------

       ui->textBrowser->setTextColor(Qt::blue);
       ui->textBrowser->append( "int  " + QString::number(MBCRC16,16));

       // ---------------------------------------------------
       */



       ij++;
       // чекаем контрольную сумму
       if (MBCRC16 == after_hex5){

           ui->textBrowser->setTextColor(Qt::blue);
           ui->textBrowser->append("Package " + QString::number(ij) + " : " +message + " ---> " + after);
           ui->textBrowser->setTextColor(Qt::black);
           ui->textBrowser->append(".....................................................................................");

           ui->label_10->setText(x_s);
           ui->label_11->setText(y_s);
           ui->label_12->setText(y_0_st);
           ui->label_14->setText(x_0_st);
           buffer.remove(0,20);
          // ui->textBrowser->setTextColor(Qt::green);
          // ui->textBrowser->append("Truly CRC16");

       }
       else {
           Sleeper::msleep(50); // нужно поспать немного на случай если пришла большая посылка
           ui->textBrowser->setTextColor(Qt::red);
           ui->textBrowser->append("FAIL IN MBCRC16!!!");
           QString message2 = buffer.mid(0,100);
           ui->textBrowser->append(message2 );
            buffer.remove(0,100);

       }  // after_hex5 - это моя исходная хэш-сумма.


      // buffer.remove(0,100); //убьет если посылка пришла больше 10 байт. если пришла меньше 10 байт то она
       // не пройдет по хэшсумме

        // посылка может быть длиннее или короче. хеш-сумма может не биться. сделать
       // так чтобы дальнейшие были нормальные
       //чекаем осталось ли что-нибудь в буфере
       if(buffer.size()!=0){
           ui->textBrowser->setTextColor(Qt::red);

           ui->textBrowser->append("buffer not empty!!!");
           QString message2 = buffer.mid(0,100);
           ui->textBrowser->append(message2);
       }
       if(tmr->isActive()){ // таймер работает, но пока не заюзан
           //ui->textBrowser->append("TMR isActive");
       }

    }



}


void Widget::on_pushButton_clicked()
{
    QString message = ui->lineEdit_2->text();
    ui->textBrowser->setTextColor(Qt::darkGreen); // Color of message to send is green.
    ui->textBrowser->append(message);
    serialPort.write(message.toUtf8());    // ЗАПИСЫВАЕМ ИНФОРМАЦИЮ
}


// Button of Disconnect
void Widget::on_pushButton_3_clicked()
{
    serialPort.close();
    buffer.remove(0,100);
    //tmr->stop();
}

/*
// Button of Refresh Ports
void Widget::on_pushButton_4_clicked()
{
    ui->comboBox->clear();
    QList<QSerialPortInfo> ports = info.availablePorts();
    QList<QString> stringPorts;
    for(int i = 0 ; i < ports.size() ; i++){       // РЕФРЕШИМ ПОРТЫ
        stringPorts.append(ports.at(i).portName());
    }
    ui->comboBox->addItems(stringPorts);
}
*/
// Button of Clear
void Widget::on_pushButton_5_clicked()
{
    ui->textBrowser->clear();
}
