#include "head.h"
#include <QDebug>
extern int currentTime;
extern customer traveller;
extern FILE *fileOutput;



void PrintTime()
{
    if (currentTime % 24 < 10)
        fprintf(fileOutput, "Day%d: 0%d:00,", currentTime / 24 + 1, currentTime % 24);
    else
        fprintf(fileOutput, "Day%d: %d:00,", currentTime / 24 + 1, currentTime % 24);
}
void PrintRoute()
{int i = 0;
    for( ;i < traveller.route.index; i++)
        fprintf(fileOutput, "%d->", traveller.route.route[i]);
    fprintf(fileOutput, "%d\n", traveller.route.route[i]);
}
