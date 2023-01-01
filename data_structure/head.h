#ifndef HEAD_H
#define HEAD_H
#include <stdio.h>
#include <queue>
#include "widget.h"
#include <QWidget>
#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

#define CITY_NUM 34         //城市总数
#define HOURS_PER_DAY 24    //每天小时数
#define MAX 65535           //最大值
#define BUS 0
#define BUS_RISK 2          //汽车风险值
#define TRAIN 1
#define TRAIN_RISK 5        //火车风险值
#define PLANE 2
#define PLANE_RISK 9        //飞机风险值
#define LOW_RISK 0.2        //低风险城市风险值
#define MIDDLE_RISK 0.5     //中风险城市风险值
#define HIGH_RISK 0.9       //高风险城市风险值
typedef struct City
{
    char name[32];      //城市名称
    float risk;         //城市风险
} city;

typedef struct Line
{
    int vehicleType;        //交通工具
    int departureInterval;  //始发时间
    int runningTime;        //运行时间
    float risk;             //路径风险
    int departureCity;      //起点城市
    int destinationCity;    //终点城市
    int nextSameOrigin;     //下一条相同始发地的线路
} line;

typedef struct Route
{
    int route[1024];    //途经城市
    int citiesPassed;   //途经城市数量
    int line[1024];     //使用交通线路
    int index;
} route;

typedef struct Customer
{
    int travellerStrategy;  //旅行策略
    int timeLimit;          //时间限制
    int departureTime;      //出发时间
    int setoff;             //是否出发
    int timer;              //计时器
    int currentCity;        //当前城市
    int departureCity;      //出发城市
    int destinationCity;    //目的城市
    int vehicle;            //当前交通工具
    int moving;             //是否在移动
    int arrival;            //是否到达
    float totalRisk;        //总风险
    struct Route route;     //乘客路径
} customer;
struct node             //用于寻路算法的结点，
{
    int ID;
    int time;
    float risk;
    bool operator < (const node &a) const
    {
        return a.risk < risk;
    }
    int departureCity;
    int lineChosen;
};

void Input();               //文件输入
void NewDestination();      //新增目的城市
void Initialize();          //初始化
void PrintTime();           //向文本输出当前时间
void PrintRoute();          //向文本输出路径
void Update();              //更新状态
route Routing(const int from, const int to, const int timeLimit, const int departureTime);//按条件寻找路径

#endif // HEAD_H


