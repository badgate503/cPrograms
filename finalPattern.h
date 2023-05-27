/*
 * makeShape.h -- 绘制两种形状相关函数接口. 
 */
 
#ifndef __FINALPATTERN_H__
#define __FINALPATTERN_H__

#include "genlib.h"
#include "tangramMain.h"
#include "linkedlist.h"

typedef struct{
    double deg;
    double len;
} *Vect;

Vect genVec(double deg,double len);
void drawVec(void *v);
void drawPattern(linkedlistADT vl,double stX,double stY);
void forwd(double distance, double toward);
void loadDis(string path);

#endif
