/*
 * makeShape.c -- 图形相关操作函数的实现
 */
  
#include <math.h>
#include <windef.h>
#include "extgraph.h"
#include "makeShape.h"
#include "tangramMain.h"

double toward = 0;
extern string shpColor[7];

Shape genShape(int type, double x, double y, double initFwd ,int initColor)
{
	Shape gShp = New(Shape);
	gShp->shapeType = type;
	gShp->x = x;
	gShp->y = y;
    gShp->rotDeg = initFwd;
    gShp->colorIndex = initColor;
    gShp->isSelected = FALSE;
    gShp->floatAbove = FALSE;
    return gShp;
}

void renderShape(void *shape, bool isFilling)
{
	if (shape == NULL) return;
	int i = 1;
	double coef = 1;
	Shape shp = (Shape)shape;
	double cX = shp->x;
	double cY = shp->y;
	SetPenSize(3);
	SetPenColor(isFilling ? shpColor[shp->colorIndex] : (shp->isSelected ? "red":(shp->floatAbove ? "black":"gray")));
	if(shp->shapeType <= 2)
	{
		if(isFilling) StartFilledRegion(1);
		
	    for(; i <= shp->shapeType; i++) coef *= 1.414213562;
		MovePen(cX,cY);
		turn(shp->rotDeg); 
		move(coef * DEFAULT_LEN * 1.414213562 / 2);
		shp->vertex[0] = New(Point);
		shp->vertex[0]->x = GetCurrentX();
		shp->vertex[0]->y = GetCurrentY();
		turn(135);
		forward(coef * DEFAULT_LEN);
		shp->vertex[1] = New(Point);
		shp->vertex[1]->x = GetCurrentX();
		shp->vertex[1]->y = GetCurrentY();
		turn(135);
		forward(coef * DEFAULT_LEN * 1.414213562);
		shp->vertex[2] = New(Point);
		shp->vertex[2]->x = GetCurrentX();
		shp->vertex[2]->y = GetCurrentY();
		turn(135);
		forward(coef * DEFAULT_LEN);
		toward = 0;
		
        if(isFilling) EndFilledRegion();
	}
	else if(shp->shapeType == 3)
	{
		if(isFilling) StartFilledRegion(1);
		
		MovePen(cX,cY);
		turn(shp->rotDeg);
		move(DEFAULT_LEN / 2);
		turn(90);
		move(DEFAULT_LEN / 2);
		shp->vertex[0] = New(Point);
		shp->vertex[0]->x = GetCurrentX();
		shp->vertex[0]->y = GetCurrentY();
		turn(90);
		forward(DEFAULT_LEN);
		shp->vertex[1] = New(Point);
		shp->vertex[1]->x = GetCurrentX();
		shp->vertex[1]->y = GetCurrentY();
		turn(90);
		forward(DEFAULT_LEN);
		shp->vertex[2] = New(Point);
		shp->vertex[2]->x = GetCurrentX();
		shp->vertex[2]->y = GetCurrentY();
		turn(90);
		forward(DEFAULT_LEN);
		shp->vertex[3] = New(Point);
		shp->vertex[3]->x = GetCurrentX();
		shp->vertex[3]->y = GetCurrentY();
		turn(90);
		forward(DEFAULT_LEN);
		toward = 0;
		
		if(isFilling) EndFilledRegion();
	}
	else if(shp->shapeType == 4)
	{
		if(isFilling) StartFilledRegion(1);
		
		MovePen(cX,cY);
		turn(shp->rotDeg);
		move(DEFAULT_LEN * 1.414213562 / 2);
		turn(135);
		move(DEFAULT_LEN / 2);
		shp->vertex[0] = New(Point);
		shp->vertex[0]->x = GetCurrentX();
		shp->vertex[0]->y = GetCurrentY();
		turn(45);
		forward(DEFAULT_LEN * 1.414213562);
		shp->vertex[1] = New(Point);
		shp->vertex[1]->x = GetCurrentX();
		shp->vertex[1]->y = GetCurrentY();
		turn(135);
		forward(DEFAULT_LEN);
		shp->vertex[2] = New(Point);
		shp->vertex[2]->x = GetCurrentX();
		shp->vertex[2]->y = GetCurrentY();
		turn(45);
		forward(DEFAULT_LEN * 1.414213562);
		shp->vertex[3] = New(Point);
		shp->vertex[3]->x = GetCurrentX();
		shp->vertex[3]->y = GetCurrentY();
		turn(135);
		forward(DEFAULT_LEN);
		toward = 0;
		
		if(isFilling) EndFilledRegion();
	}
}

bool isInside(void *shape, Point p)
{
	Shape shp = (Shape)shape;
	int dtm;
	if(shp->shapeType<=2){
		dtm += isIntersect(shp->vertex[0],shp->vertex[1],p);
		dtm += isIntersect(shp->vertex[1],shp->vertex[2],p);
		dtm += isIntersect(shp->vertex[2],shp->vertex[0],p);
	}else{
		dtm += isIntersect(shp->vertex[0],shp->vertex[1],p);
		dtm += isIntersect(shp->vertex[1],shp->vertex[2],p);
		dtm += isIntersect(shp->vertex[2],shp->vertex[3],p);
		dtm += isIntersect(shp->vertex[3],shp->vertex[0],p);
	}
		
	//printf("$$ %lf %lf $$ %lf %lf $$ %lf %lf $$",shp->vertex[0]->x,shp->vertex[0]->y,shp->vertex[1]->x,shp->vertex[1]->y,shp->vertex[2]->x,shp->vertex[2]->y);
	return dtm == 1;
}

int isIntersect(Point p1,Point p2,Point p3)
{
	double sectX;
	if(p1->y == p2->y)
	{
		return 0;
	}
	else
	{
		sectX = (p3->y - p1->y) * (p1->x - p2->x) / (p1->y - p2->y) + p1->x;
		return (p3->y >= Minf(p1->y, p2->y) && p3->y <= Maxf(p1->y, p2->y) && sectX > p3->x) ? 1 : 0;
	}
}
/*
 * Function: forward
 * Usage: forward(distance);
 * -----------------------------------
 * Draw a line along the current direction, 
 * the length is distance, back when distance 
 * is negative
 */

void forward(double distance)
{
	double movx = distance * cos(degToRad(toward));
	double movy = distance * sin(degToRad(toward));
	//MovePen(cx+movx,yCenter);
	DrawLine(movx,movy);
}

/*
 * Function: turn
 * Usage: turn(angle);
 * -----------------------------------
 * Rotate the angle angle clockwise, the angle unit 
 * is DEG, and rotate counterclockwise when the angle 
 * is negative.
 */

void turn (double angle)
{
	toward += angle;
	while(toward >= 360)
	{
		toward -= 360;
	}
	while(toward < 0)
	{
		toward += 360;
	}
}

/*
 * Function: move
 * Usage: move(distance);
 * -----------------------------------
 * Move the pen along the current direction (do not 
 * draw a line), the length is distance, when the 
 * distance is a negative number, move back.
 */

void move(double distance)
{
	double movx = distance * cos(degToRad(toward));
	double movy = distance * sin(degToRad(toward));
	MovePen(GetCurrentX()+movx,GetCurrentY()+movy);
}

/*
 * Function: degToRad
 * Usage: rad = degToRad(deg);
 * -----------------------------------
 * This function converts deg to rad.
 */
 
double degToRad(double deg){
	return 3.141592654*(deg/180);
}

double Minf(double x, double y)
{
    return ((x < y) ? x : y);
}

double Maxf(double x, double y)
{
    return ((x > y) ? x : y);
}


