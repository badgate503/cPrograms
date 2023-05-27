#ifndef __TIMER_H
#define __TIMER_H

#include "genlib.h"
#include "graphics.h" 

void Timer(double maxT, bool isStop);
void EraseTime(double x,double y);
string TimeToString(int m,int s);

#endif
