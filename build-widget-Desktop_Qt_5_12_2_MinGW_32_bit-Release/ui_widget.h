/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QTextBrowser *textBrowser;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(984, 657);
        textBrowser = new QTextBrowser(Widget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(20, 400, 901, 201));
        QFont font;
        font.setPointSize(14);
        textBrowser->setFont(font);
        textBrowser->viewport()->setProperty("cursor", QVariant(QCursor(Qt::CrossCursor)));
        lineEdit_2 = new QLineEdit(Widget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(490, 50, 431, 111));
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(850, 180, 71, 31));
        pushButton_2 = new QPushButton(Widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(20, 340, 81, 51));
        pushButton_3 = new QPushButton(Widget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(110, 340, 81, 51));
        pushButton_5 = new QPushButton(Widget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(810, 610, 111, 41));
        label_8 = new QLabel(Widget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(570, 240, 41, 21));
        QFont font1;
        font1.setPointSize(18);
        font1.setBold(false);
        font1.setWeight(50);
        label_8->setFont(font1);
        label_9 = new QLabel(Widget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(810, 240, 47, 21));
        label_9->setFont(font1);
        label_10 = new QLabel(Widget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(490, 280, 201, 111));
        QFont font2;
        font2.setPointSize(36);
        label_10->setFont(font2);
        label_10->setAutoFillBackground(false);
        label_10->setFrameShape(QFrame::StyledPanel);
        label_11 = new QLabel(Widget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(720, 280, 201, 111));
        label_11->setFont(font2);
        label_11->setFrameShape(QFrame::StyledPanel);
        label_11->setFrameShadow(QFrame::Plain);
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 10, 441, 131));
        QFont font3;
        font3.setFamily(QString::fromUtf8("TechnicBold"));
        font3.setPointSize(36);
        label->setFont(font3);
        label_12 = new QLabel(Widget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(250, 210, 201, 111));
        label_12->setFont(font2);
        label_12->setFrameShape(QFrame::StyledPanel);
        label_12->setFrameShadow(QFrame::Plain);
        label_13 = new QLabel(Widget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(340, 170, 47, 21));
        label_13->setFont(font1);
        label_14 = new QLabel(Widget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(20, 210, 201, 111));
        label_14->setFont(font2);
        label_14->setAutoFillBackground(false);
        label_14->setFrameShape(QFrame::StyledPanel);
        label_15 = new QLabel(Widget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(100, 170, 41, 21));
        label_15->setFont(font1);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        pushButton->setText(QApplication::translate("Widget", "Send", nullptr));
        pushButton_2->setText(QApplication::translate("Widget", "Connect", nullptr));
        pushButton_3->setText(QApplication::translate("Widget", "Disconnect", nullptr));
        pushButton_5->setText(QApplication::translate("Widget", "Clear", nullptr));
        label_8->setText(QApplication::translate("Widget", "\316\224X", nullptr));
        label_9->setText(QApplication::translate("Widget", "\316\224Y", nullptr));
        label_10->setText(QString());
        label_11->setText(QString());
        label->setText(QApplication::translate("Widget", "Terminal  v.1.0.", nullptr));
        label_12->setText(QString());
        label_13->setText(QApplication::translate("Widget", "Y0", nullptr));
        label_14->setText(QString());
        label_15->setText(QApplication::translate("Widget", "X0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
