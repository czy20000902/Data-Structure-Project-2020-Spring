#include "head.h"
#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>
#include <QMessageBox>
#include <QTimer>
#include <QPainter>
#include <QPalette>
#include <QDebug>
#include <QMouseEvent>
extern customer traveller;
extern line lineList[1024];
extern int currentTime,departureTime,timeLimit;
extern int departureCity, destinationCity;
extern bool travellerStrategy;
extern int newDestination;
extern char vehicleName[3][16];
extern city cityList[CITY_NUM];
extern FILE *fileOutput;
void NewDestination()
{
    newDestination=0;
    traveller.departureTime = departureTime;
    traveller.travellerStrategy = travellerStrategy;
    if (traveller.travellerStrategy)
        traveller.timeLimit = timeLimit;
    else
        traveller.timeLimit = MAX;
    traveller.departureCity = departureCity;
    traveller.destinationCity = destinationCity;
    traveller.arrival = 0;
    traveller.moving = 0;
    traveller.setoff = 0;
    traveller.route = Routing(departureCity, destinationCity, traveller.timeLimit, departureTime);
}
void Update()
{
    if(traveller.setoff == 0)
    {
        if (traveller.route.route[0] == -1)
            traveller.arrival = 1, fprintf(fileOutput,"Impossible to arrive on time.\n");
        else if (traveller.departureTime == currentTime)//旅客按时出发
            PrintTime(), fprintf(fileOutput, " traveller sets off on time.\n"), traveller.timer = currentTime, traveller.setoff = 1;
        else if (traveller.departureTime < currentTime)//旅客晚点出发
            PrintTime(), fprintf(fileOutput, " traveller sets off late.\n"), traveller.timer = currentTime, traveller.setoff = 1;
        else if (traveller.departureTime > currentTime)//旅客在始发地等待
        {
            PrintTime();
            traveller.moving = 0;
            fprintf(fileOutput, " traveller is waiting at %s, risk of being infected is %.1f\n",
                    cityList[traveller.currentCity].name, traveller.totalRisk);
        }
    }
    else if (currentTime % lineList[traveller.route.line[traveller.route.index]].departureInterval == 0 && traveller.moving == 0)
    {//如果到了旅客所乘路线的发车时间，则输出乘坐的交通工具
        traveller.timer = currentTime, traveller.moving = 1, traveller.vehicle=lineList[traveller.route.line[traveller.route.index]].vehicleType;
        PrintTime();
        fprintf(fileOutput , " traveller boards the %s, risk of being infected is %.1f\n",
                vehicleName[lineList[traveller.route.line[traveller.route.index]].vehicleType], traveller.totalRisk);
    }
    else if (traveller.timer + lineList[traveller.route.line[traveller.route.index]].runningTime == currentTime && traveller.moving == 1)
    {//如果旅客班次始发时间加上行动时间等于计时器，则班次到站
        if (traveller.route.index + 1 == traveller.route.citiesPassed)
        {
            traveller.currentCity = traveller.destinationCity, traveller.moving = 0, traveller.arrival = 1, traveller.setoff = 0;
            traveller.timer = currentTime;
            if(!newDestination)
                departureCity = traveller.currentCity;
            PrintTime();
            fprintf(fileOutput , " traveller has arrived at destination %s, risk of being infected is %.1f\n",
                    cityList[traveller.destinationCity].name, traveller.totalRisk);
        }
        else
        {
            traveller.currentCity = lineList[traveller.route.line[traveller.route.index]].destinationCity;
            traveller.timer = currentTime;
            PrintTime();
            fprintf(fileOutput , " traveller has arrived at %s, risk of being infected is %.1f\n",
                    cityList[traveller.currentCity].name, traveller.totalRisk);
            traveller.route.index++;
        }
    }
    else if(traveller.moving)
    {
        PrintTime();
        fprintf(fileOutput , " traveller is travelling on %s, risk of being infected is %.1f\n",
                vehicleName[lineList[traveller.route.line[traveller.route.index]].vehicleType], traveller.totalRisk);
    }
    else
    {
        PrintTime();
        fprintf(fileOutput, " traveller is waiting at %s, risk of being infected is %.1f\n",
                cityList[traveller.currentCity].name, traveller.totalRisk);
    }
}
