/*
 * makeShape.h -- 绘制两种形状相关函数接口. 
 */

#ifndef __MAKESHAPE_H__
#define __MAKESHAPE_H__

#define DEFAULT_COLOR "black"
#define DEFAULT_DEG 0
#define DEFAULT_LEN 1.0

#include "genlib.h"
#include "tangramMain.h"
#include "Save.h"

typedef struct {
	double x, y;
} *Point;

typedef struct {
	int shapeType; //0~2 等腰三角形，1 -- 正方形， 2 -- 平行四边形. 
	double x, y;
    double rotDeg; //旋转角度.为45的整数倍. 
    int colorIndex;
    bool isSelected;
    bool floatAbove;
    bool isVisible;
    Point vertex[4];
} *Shape;

Shape genShape(int type,double x, double y, double initFwd, int initColor);
int isIntersect(Point p1,Point p2,Point p3);
bool isInside(void *shape, Point p);
void renderShape(void *shape, bool isFilling);
void forward(double distance);
void turn (double angle);
void move(double distance);
double degToRad(double deg);
double Maxf(double x, double y);
double Minf(double x, double y);
#endif
