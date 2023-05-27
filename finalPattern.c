/*
 * makeShape.c -- 图形相关操作函数的实现
 */
  
#include <math.h>
#include <windef.h>
#include "extgraph.h"
#include "finalPattern.h"
#include "tangramMain.h"
#include "linkedlist.h"


Vect genVec(double deg,double len)
{
	Vect vec = New(Vect);
	vec->deg = deg;
	vec->len = len;
	return vec;
}

void drawVec(void *v)
{
	if (v == NULL) return;
	Vect vec = (Vect)v;
	forwd(vec->len, vec->deg);
}

void drawPattern(linkedlistADT vl, double stX,double stY)
{
	MovePen(stX,stY);
	string pk = GetPenColor();
	SetPenColor("black");
	TraverseLinkedList(vl, drawVec);
	SetPenColor(pk);
}

/*
 * Function: forward
 * Usage: forward(distance);
 * -----------------------------------
 * Draw a line along the current direction, 
 * the length is distance, back when distance 
 * is negative
 */

void forwd(double distance, double toward)
{
	double movx = distance * cos(degToRad(toward));
	double movy = distance * sin(degToRad(toward));
	//MovePen(cx+movx,yCenter);
	DrawLine(movx,movy);
}



