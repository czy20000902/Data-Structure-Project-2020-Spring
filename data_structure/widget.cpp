#include "widget.h"
#include "ui_widget.h"
#include "head.h"
#include <QPushButton>
#include <QMessageBox>
#include <QTimer>
#include <QPainter>
#include <QPalette>
#include <QDebug>
#include <QMouseEvent>

extern int currentTime, departureTime, timeLimit;
extern int departureCity, destinationCity;
extern bool travellerStrategy;
extern int newDestination;
extern line lineList[1024];
extern customer traveller;
extern char vehicleName[3][16];
extern city cityList[CITY_NUM];
extern line lineList[1024];
QTimer * UITime;
//QPalette palette;
//QPixmap arrayImage("map.png"); //图片路径
//QRect arrayRect(); //截取图片区域
QPainter painter;
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


    UITime = new QTimer(this);
    UITime->start(3000);

    connect(UITime, &QTimer::timeout,[=]()
    {
        if(newDestination && traveller.arrival)
            NewDestination();
        else if(!traveller.arrival)
            Update();
        if(currentTime % HOURS_PER_DAY < 10)
        {
            str = QString::fromStdString("Day")
                    + QString::number(currentTime / 24 + 1)
                    + QString::fromStdString(": 0")
                    + QString::number(currentTime % 24)
                    + QString::fromStdString(":00");
        }
        else
        {
            str = QString::fromStdString("Day")
                    + QString::number(currentTime / 24 + 1)
                    + QString::fromStdString(": ")
                    + QString::number(currentTime % 24)
                    + QString::fromStdString(":00");
        }
        ui->textBrowser_8->setText(str);
        currentTime++;
        str = QString::fromStdString(cityList[traveller.currentCity].name);
        ui->textBrowser_9->setText(str);
        str = QString::fromStdString(cityList[traveller.destinationCity].name);
        ui->textBrowser_10->setText(str);
        str = QString::fromStdString(vehicleName[traveller.vehicle]);
        ui->textBrowser_11->setText(str);
        ui->textBrowser_12->setText(QString::number(traveller.totalRisk));
        if(travellerStrategy)
            str = QString::fromStdString("[限时最低风险]");
        else
            str = QString::fromStdString("[最低风险] ");
        ui->textBrowser_13->setText(str);
        ui->textBrowser_14->setText(QString::number(departureTime));
        ui->textBrowser_15->setText(QString::number(timeLimit));
        if(!traveller.setoff)
            str = "[等待中]" + QString::fromStdString(cityList[traveller.currentCity].name);
        else if(!traveller.arrival)
            str = QString::fromStdString(cityList[traveller.currentCity].name)
                + "->"
                + QString::fromStdString(cityList[lineList[traveller.route.line[traveller.route.index]].destinationCity].name);
        else
            str = "[已到达]"+QString::fromStdString(cityList[traveller.currentCity].name);
        ui->textBrowser_16->setText(str);
        if (newDestination && traveller.route.route[0] == -1)
            newDestination = 0, ui->textBrowser_17->setText("[无法满足时间限制]");
        else if(newDestination)
            str = QString::fromStdString(cityList[destinationCity].name),
            ui->textBrowser_17->setText(str);
        else
            ui->textBrowser_17->setText("[无]");
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_0_clicked()
{
    departureCity = destinationCity;
    destinationCity = 0;
    newDestination = 1;
}
void Widget::on_pushButton_1_clicked()
{
    departureCity = destinationCity;
    destinationCity = 1;
    newDestination = 1;
}
void Widget::on_pushButton_2_clicked()
{
    departureCity = destinationCity;
    destinationCity = 2;
    newDestination = 1;
}
void Widget::on_pushButton_3_clicked()
{
    departureCity = destinationCity;
    destinationCity = 3;
    newDestination = 1;
}
void Widget::on_pushButton_4_clicked()
{
    departureCity = destinationCity;
    destinationCity = 4;
    newDestination = 1;
}
void Widget::on_pushButton_5_clicked()
{
    departureCity = destinationCity;
    destinationCity = 5;
    newDestination = 1;
}
void Widget::on_pushButton_6_clicked()
{
    departureCity = destinationCity;
    destinationCity = 6;
    newDestination = 1;
}
void Widget::on_pushButton_7_clicked()
{
    departureCity = destinationCity;
    destinationCity = 7;
    newDestination = 1;
}
void Widget::on_pushButton_8_clicked()
{
    departureCity = destinationCity;
    destinationCity = 8;
    newDestination = 1;
}
void Widget::on_pushButton_9_clicked()
{
    departureCity = destinationCity;
    destinationCity = 9;
    newDestination = 1;
}
void Widget::on_pushButton_10_clicked()
{
    departureCity = destinationCity;
    destinationCity = 10;
    newDestination = 1;
}
void Widget::on_pushButton_11_clicked()
{
    departureCity = destinationCity;
    destinationCity = 11;
    newDestination = 1;
}
void Widget::on_pushButton_12_clicked()
{
    departureCity = destinationCity;
    destinationCity = 12;
    newDestination = 1;
}
void Widget::on_pushButton_13_clicked()
{
    departureCity = destinationCity;
    destinationCity = 13;
    newDestination = 1;
}
void Widget::on_pushButton_14_clicked()
{
    departureCity = destinationCity;
    destinationCity = 14;
    newDestination = 1;
}
void Widget::on_pushButton_15_clicked()
{
    departureCity = destinationCity;
    destinationCity = 15;
    newDestination = 1;
}
void Widget::on_pushButton_16_clicked()
{
    departureCity = destinationCity;
    destinationCity = 16;
    newDestination = 1;
}
void Widget::on_pushButton_17_clicked()
{
    departureCity = destinationCity;
    destinationCity = 17;
    newDestination = 1;
}
void Widget::on_pushButton_18_clicked()
{
    departureCity = destinationCity;
    destinationCity = 18;
    newDestination = 1;
}
void Widget::on_pushButton_19_clicked()
{
    departureCity = destinationCity;
    destinationCity = 19;
    newDestination = 1;
}
void Widget::on_pushButton_20_clicked()
{
    departureCity = destinationCity;
    destinationCity = 20;
    newDestination = 1;
}
void Widget::on_pushButton_21_clicked()
{
    departureCity = destinationCity;
    destinationCity = 21;
    newDestination = 1;
}
void Widget::on_pushButton_22_clicked()
{
    departureCity = destinationCity;
    destinationCity = 22;
    newDestination = 1;
}
void Widget::on_pushButton_23_clicked()
{
    departureCity = destinationCity;
    destinationCity = 23;
    newDestination = 1;
}
void Widget::on_pushButton_24_clicked()
{
    departureCity = destinationCity;
    destinationCity = 24;
    newDestination = 1;
}
void Widget::on_pushButton_25_clicked()
{
    departureCity = destinationCity;
    destinationCity = 25;
    newDestination = 1;
}
void Widget::on_pushButton_26_clicked()
{
    departureCity = destinationCity;
    destinationCity = 26;
    newDestination = 1;
}
void Widget::on_pushButton_27_clicked()
{
    departureCity = destinationCity;
    destinationCity = 27;
    newDestination = 1;
}
void Widget::on_pushButton_28_clicked()
{
    departureCity = destinationCity;
    destinationCity = 28;
    newDestination = 1;
}
void Widget::on_pushButton_29_clicked()
{
    departureCity = destinationCity;
    destinationCity = 29;
    newDestination = 1;
}
void Widget::on_pushButton_30_clicked()
{
    departureCity = destinationCity;
    destinationCity = 30;
    newDestination = 1;
}
void Widget::on_pushButton_31_clicked()
{
    departureCity = destinationCity;
    destinationCity = 31;
    newDestination = 1;
}
void Widget::on_pushButton_32_clicked()
{
    departureCity = destinationCity;
    destinationCity = 32;
    newDestination = 1;
}
void Widget::on_pushButton_33_clicked()
{
    departureCity = destinationCity;
    destinationCity = 33;
    newDestination = 1;
}
void Widget::on_pushButton_37_clicked()
{
    travellerStrategy = !travellerStrategy;
    if(travellerStrategy)
        str = QString::fromStdString("[限时最低风险]");
    else
        str = QString::fromStdString("[最低风险] ");
    ui->textBrowser_13->setText(str);
}
void Widget::on_pushButton_38_clicked()
{
    departureTime --;
    ui->textBrowser_14->setText(QString::number(departureTime));
}
void Widget::on_pushButton_39_clicked()
{
    departureTime ++;
    ui->textBrowser_14->setText(QString::number(departureTime));
}
void Widget::on_pushButton_40_clicked()
{
    departureTime -= 10;
    ui->textBrowser_14->setText(QString::number(departureTime));
}
void Widget::on_pushButton_41_clicked()
{
    departureTime += 10;
    ui->textBrowser_14->setText(QString::number(departureTime));
}
void Widget::on_pushButton_42_clicked()
{
    timeLimit-= 10;
    ui->textBrowser_15->setText(QString::number(timeLimit));
}
void Widget::on_pushButton_43_clicked()
{
    timeLimit--;
    ui->textBrowser_15->setText(QString::number(timeLimit));
}
void Widget::on_pushButton_44_clicked()
{
    timeLimit ++;
    ui->textBrowser_15->setText(QString::number(timeLimit));
}
void Widget::on_pushButton_45_clicked()
{
    timeLimit += 10;
    ui->textBrowser_15->setText(QString::number(timeLimit));
}
void Widget::on_pushButton_46_clicked(){UITime->stop();}
void Widget::on_pushButton_47_clicked(){UITime->start(3000);}

void Widget::on_pushButton_clicked()
{
    close();
}
