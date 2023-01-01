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

extern city cityList[CITY_NUM];
extern line lineList[1024];
extern int sameOrigin[1024];
extern FILE *fileInput;
extern customer traveller;
extern int LineNum;
extern int departureCity, destinationCity;
extern int timeLimit;
extern bool travellerStrategy;
extern int departureTime;

void Initialize()
{
    lineList[0].nextSameOrigin = -1;
    traveller.departureTime = 0;
    traveller.destinationCity = traveller.departureCity = 0;
    traveller.setoff = 0;
    traveller.travellerStrategy = 0;
    traveller.timeLimit = 0;
    traveller.moving = 0;
    traveller.arrival = 1;
    traveller.timer = 0;
}

void Input()
{
    int i = 0;

    for (int j = 0; j < CITY_NUM; j++)
        fscanf(fileInput,"%f%s", &cityList[j].risk,cityList[j].name);
    fscanf(fileInput,"%d", &LineNum);
    for (int j = 0; j < LineNum; j++)
    {
        fscanf(fileInput,"%d%d%d%d%d", &lineList[j].vehicleType,&lineList[j].departureCity,&lineList[j].destinationCity,&lineList[j].departureInterval,&lineList[j].runningTime);
        switch(lineList[j].vehicleType)
        {
        case BUS:
            lineList[j].risk = lineList[j].runningTime * BUS_RISK * cityList[lineList[j].departureCity].risk;
            break;
        case TRAIN:
            lineList[j].risk = lineList[j].runningTime * TRAIN_RISK * cityList[lineList[j].departureCity].risk;
            lineList[j].departureInterval = 2 * lineList[j].runningTime;
            break;
        case PLANE:
            lineList[j].risk = lineList[j].runningTime * PLANE_RISK * cityList[lineList[j].departureCity].risk;
            lineList[j].departureInterval = 2 * lineList[j].runningTime;
            break;
        }
        lineList[j].nextSameOrigin = sameOrigin[lineList[j].departureCity]; //记录所有始发地相同的线路
        sameOrigin[lineList[j].departureCity] = i, i++;
    }
}
