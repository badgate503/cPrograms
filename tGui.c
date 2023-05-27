/*
 * makeShape.c -- 图形相关操作函数的实现
 */
  
#include <math.h>
#include <windef.h>
#include "extgraph.h"
#include "tGui.h"
#include "tangramMain.h"

double aT, aL;


Button genBtn(double top,double left,double width,double height,string label,int fontSize)
{
	Button gBtn = New(Button);
	gBtn->top = top;
	gBtn->left = left;
	gBtn->width = width;
	gBtn->height = height;
	gBtn->isShow = TRUE;
	gBtn->floatAbove = FALSE;
	gBtn->isClicked = FALSE;
	gBtn->label = label;
	gBtn->fontSize = fontSize;
    return gBtn;
}

void renderBtn(Button btn)
{
	aT = GetWindowHeight() - btn->top;
	aL = btn->left;
	SetFont("arial");
	SetPointSize(btn->fontSize);
	MovePen(aL + (btn->width - TextStringWidth(btn->label)) / 2, aT - (btn->height + (1.0*btn->fontSize/200)) / 2);
	SetPenColor("btn_text");
	DrawTextString(btn->label);
	MovePen(aL + (btn->width - TextStringWidth(btn->label)) / 2, aT - (btn->height + (1.0*btn->fontSize/200)) / 2 - 0.07);
	SetPenColor(btn->isClicked ? "btn_clicked" : (btn->floatAbove ? "btn_above" : "btn_normal"));
	StartFilledRegion(1);
	DrawLine(TextStringWidth(btn->label),0);
	DrawLine(0,-0.05);
	DrawLine(-TextStringWidth(btn->label),0);
	DrawLine(0,0.05);
	EndFilledRegion();
	
}

bool isInsideBtn(Button btn, double x, double y)
{
	aT = GetWindowHeight() - btn->top;
	aL = btn->left;
	return (x >= aL) && (x <= aL + btn->width) && (y <= aT) &&(y >= aT - btn->height);
}
