#include "widget.h"
#include "head.h"
#include <QDebug>

extern FILE * fileOutput;
extern int sameOrigin[1024], currentTime;
extern customer traveller;
extern line lineList[1024];
extern city cityList[CITY_NUM];

route Routing(const int from, const int to, const int timeLimit, const int departureTime)
{
    route prepareRoute;
    int routingComplete = 0;
    int index, i, t;
    int timer;                      //计时器
    int departure;                  //出发时间
    int pre[256];                   //记录各节点线路起点
    int preRoutes[256];             //记录各节点线路
    int route[256];
    int pathRoutes[256];
    int visited[256] = { 0 };
    node currentNode;               //当前节点
    node nextNode;                  //下一节点
    priority_queue <node> q;        //优先队列
    currentNode.ID = from;
    currentNode.time = 0;
    currentNode.risk = 0;
    currentNode.departureCity = from;
    currentNode.lineChosen = 0;
    q.push(currentNode);
    float countRisk = MAX;
    while (!q.empty()&&routingComplete == 0)
    {
        currentNode = q.top();
        timer = currentNode.time + departureTime;
        q.pop();
        if (visited[currentNode.ID])                        //若已访问过当前节点
            continue;
        visited[currentNode.ID] = 1;                        //访问当前节点
        pre[currentNode.ID] = currentNode.departureCity;    //记录当前节点线路起点
        preRoutes[currentNode.ID] = currentNode.lineChosen; //记录当前节点线路
        if (currentNode.ID == to)                           //若找到目的城市
        {
            countRisk = currentNode.risk;                   //计录风险
            break;
        }
        for (index = sameOrigin[currentNode.ID]; index >= 0; index = lineList[index].nextSameOrigin)
        {
            if (visited[lineList[index].destinationCity])            //若已访问过当前线路终点
                continue;
            t = currentTime / lineList[index].departureInterval + 1;
            departure =  t * lineList[index].departureInterval;
            while (departure < timer)
                departure += lineList[index].departureInterval;
            if (currentNode.time + lineList[index].runningTime + departure - timer <= timeLimit)   //如果超时则放弃路径
            {
                nextNode.lineChosen = index;                        //选择线路
                nextNode.ID = lineList[index].destinationCity;      //下一节点为线路终点
                nextNode.risk = lineList[index].risk + currentNode.risk + cityList[lineList[index].departureCity].risk * (departure - timer);
                nextNode.time = lineList[index].runningTime + currentNode.time + departure - timer;
                nextNode.departureCity = lineList[index].departureCity;
                if (nextNode.ID == to)                           //若找到目的城市
                {
                    pre[nextNode.ID] = nextNode.departureCity;    //记录当前节点线路起点
                    preRoutes[nextNode.ID] = nextNode.lineChosen; //记录当前节点线路
                    countRisk = nextNode.risk;                   //计录风险
                    routingComplete = 1;
                }
                q.push(nextNode);
            }
        }
    }
    if (countRisk < MAX)            //寻得路径
    {
        traveller.totalRisk = countRisk;
        index = to;                 //从终点开始
        i = 0;
        while (index != from)       //当未找到起点时
        {
            route[i] = pre[index];  //令为当前线路起点
            pathRoutes[i] = preRoutes[index], i++;
            index = pre[index];     //取当前线路起点
        }
        prepareRoute.citiesPassed = i, i--;
        for (index = 0; index < prepareRoute.citiesPassed; index++)
        {
            prepareRoute.line[index] = pathRoutes[i];
            prepareRoute.route[index] = route[i], i--;
        }
        prepareRoute.route[index] = to;
        prepareRoute.index = 0;
        return prepareRoute;
    }
    else
    {
        prepareRoute.route[0] = -1;
        prepareRoute.citiesPassed = -1;
        return prepareRoute;
    }
}
