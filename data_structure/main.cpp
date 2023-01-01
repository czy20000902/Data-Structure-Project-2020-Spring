#include "widget.h"
#include <QApplication>
#include "head.h"
#include "widget.h"

int LineNum;                    //线路总数
int sameOrigin[1024];           //相同始发地交通线路
int currentTime = 0;            //当前时间
int departureCity = 0;          //始发城市
int destinationCity = 0;        //目的城市
int timeLimit = 0;              //时间限制
bool travellerStrategy = 0;     //出行策略
int departureTime = 0;          //出发时间
int newDestination = 0;         //新增目的城市
char vehicleName[3][16]={"[汽车]","[火车]","[飞机]"};
city cityList[CITY_NUM];        //城市结构体数组
line lineList[1024];            //交通线路结构体数组
customer traveller;             //旅客结构体
FILE *fileInput, *fileOutput;   //输入/输出文件

int main(int argc, char *argv[])
{
    fileInput = fopen("Input.txt","r");
    fileOutput =fopen("output.txt","w+");
    memset(sameOrigin, 0, sizeof(sameOrigin));
    Input();
    Initialize();
    QApplication a(argc, argv);
    Widget w;
    w.setAutoFillBackground(true);
    QPalette palette;
    QPixmap pixmap(":/resource/map/map.png");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    w.setPalette(palette);
    w.show();
    w.show();
    return a.exec();
}
