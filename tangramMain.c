/*
 * File: mouseDraw.c
 * -------------
 * This program draws with the mouse.
 */
#define DEMO_BUTTON
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "graphics.h"
#include "extgraph.h" 
#include "genlib.h"
#include "conio.h"
#include <windows.h>
#include <olectl.h>
#include <stdio.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include <math.h>
#include "makeShape.h"
#include "Save.h"
#include "tGui.h"
#include "timer.h"
#include <commdlg.h>
#include "finalPattern.h"

void initTangrams(bool isDefault);
void initUI();
void updateDisplay(int area);
void ButtonEventProcess(int btnIndex);
void MouseEventProcess(int x, int y, int button, int event);
void TimerEventProcess(int timerID);
void clearArea(double left, double bottom, double width, double height);
bool isInBound(Point p);
void DefineColorRGB(string cName, double r,double g,double b);

Shape shpList[7];//good one
Button btnList[BTN_NUM];
Button uiBtnList[BTN_NUM_UI];
string shpColor[7] = {"tBrown","tViolet","tOrange","tRed","tBlue","tGreen","tYellow"};
string gameList[GAME_NUM] = {"����","���"};
string pathList[GAME_NUM] = {"square.tgm","swan.tgm"};
int chooseGameIndex = 0;
linkedlistADT vecList = NULL;
linkedlistADT disList = NULL;
Button btn_test;
int i, j =0,k;
double xCenter, yCenter;

int test_save = 0;
bool inED = FALSE; 
double px = 0.0, py = 0.0;
double sX,sY;
bool isDragging = FALSE;
bool clickingBtn = FALSE;
bool isInGame = FALSE;
string gameTitle = "Tangram";
Point mouseP;
Shape tmpShp;
/* Main program */

void Main()
{
    InitGraphics();
	SetPenSize(5);
	SetWindowTitle("Tangram game");
	DefineColor("btn_normal",1, 1, 1);
	DefineColor("btn_above",0.4, 0.4, 0.4);
	DefineColor("btn_clicked",0.2, 0.2, 0.2);
	DefineColor("btn_text",0.1, 0.1, 0.1);
	DefineColorRGB("tBrown",190, 77, 0);
	DefineColorRGB("tViolet",135, 24, 157);
	DefineColorRGB("tOrange",241, 128, 58);
	DefineColorRGB("tRed",223, 70, 97);
	DefineColorRGB("tBlue",0, 114, 206);
	DefineColorRGB("tGreen",108, 194, 74);
	DefineColorRGB("tYellow",218, 170, 0);

	mouseP = New(Point);
    tmpShp = New(Shape);
    xCenter = GetWindowWidth() / 2;
    yCenter = GetWindowHeight() / 2;
	//OpenConsole();
	vecList = NewLinkedList();
	disList = NewLinkedList();
	registerMouseEvent(MouseEventProcess);
	registerTimerEvent(TimerEventProcess);
	initUI();
	//isInGame=TRUE;
	//initTangrams();
}

void TimerEventProcess(int timerID)
{
	if(timerID == 0){
		Timer(120.0, FALSE);
	}
}

void initUI()
{
	double baseHeight = GetWindowHeight()-2.5;
	
	uiBtnList[0] = genBtn(4,1.3,1,0.5,"��ʼ",35);
	uiBtnList[1] = genBtn(5,1.3,1,0.5,"����",35);
	uiBtnList[2] = genBtn(6,1.3,1,0.5,"����",35);
	uiBtnList[3] = genBtn(7,1.3,1,0.5,"�˳�",35);
	uiBtnList[4] = genBtn(4,3,0.5,0.5,"��",35);
	uiBtnList[5] = genBtn(4,5,0.5,0.5,"��",35);
	SetPenColor("black");
	DisplayClear();
	loadDis(pathList[chooseGameIndex]);
	MovePen(3.9,GetWindowHeight() - 4.3);
	SetPointSize(35);
	printf("%d ",GetPointSize());
	DrawTextString(gameList[chooseGameIndex]);
	updateDisplay(3);
	SetPointSize(190);
	MovePen(1,baseHeight);
	SetFont("Broadway");
	for(i = 0;i < 7;i++)
	{
		SetPenColor(shpColor[i]);
		DrawTextString(CharToString(IthChar(gameTitle, i)));
	} 
	
}

void initTangrams(bool isDefault)
{
	double Pt,Pl;
    
	Pl = 1.6;
	Pt = yCenter + 1.7;
	if(isDefault)
	{
		shpList[0] = genShape(2,Pl+0.5,Pt,135,0);
		shpList[1] = genShape(2,Pl+1,Pt,315,1);
		shpList[2] = genShape(1,Pl+0.21,Pt-2,135,2);
		shpList[3] = genShape(0,Pl+0.3,Pt-2.2,315,3);
		shpList[4] = genShape(0,Pl+1.5,Pt-2.2,135,4);
		shpList[5] = genShape(3,Pl,Pt-3.5,0,5);
		shpList[6] = genShape(4,Pl+1.6,Pt-3.3,90,6);
	}
	btnList[0] = genBtn(.1,0.1,1,0.5,"������Ϸ",20);
	btnList[1] = genBtn(.1,1.6,1,0.5,"������Ϸ",20);
	btnList[2] = genBtn(.1,3.1,0.5,0.5,"��",30);
	btnList[3] = genBtn(.1,4.1,1,0.5,"����",20);
	btnList[4] = genBtn(.1,5.6,1,0.5,"���ز˵�",20);
	updateDisplay(0);
	
	startTimer(0,250);
	isDragging = FALSE;
    clickingBtn = FALSE;
    
}

void updateDisplay(int area)
{
	if(area == 0 || area == 2 && isInGame)
	{
		for(i = 0; i < BTN_NUM; i++)
		{
			renderBtn(btnList[i]);
		}
	}
	if(area == 3)
	{
		for(i = 0; i < BTN_NUM_UI; i++)
		{
			renderBtn(uiBtnList[i]);
		}
	}
	if(area == 0 || area == 1)
	{
		clearArea(0,0,GetWindowWidth(),GetWindowHeight()-0.62);
		for(i = 0; i < 7; i++)
		{
			renderShape(shpList[i],TRUE);
			renderShape(shpList[i],FALSE);
		}
	}
	if(vecList != NULL && isInGame) drawPattern(vecList,sX,GetWindowHeight() - sY);
	if(!isInGame) drawPattern(disList,sX,GetWindowHeight() - sY);
}


void clearArea(double left, double bottom, double width, double height)
{
	SetEraseMode(TRUE);
	StartFilledRegion(1);
	MovePen(left,bottom);
	DrawLine(width, 0);
	DrawLine(0,height);
	DrawLine(-width,0);
	DrawLine(0,-height);
	EndFilledRegion();
	SetEraseMode(FALSE);
}



/*
 * Function: MouseEventProcess
 * -----------------------------------
 * Called up by the external device
 */
 
void MouseEventProcess(int x, int y, int button, int event)
{
	mouseP->x = ScaleXInches(x);
	mouseP->y = ScaleYInches(y);
	if(!isInGame)
	{
		for(j = 0; j < BTN_NUM_UI;j++)
		{
			if(isInsideBtn(uiBtnList[j], mouseP->x, mouseP->y))
			{
				uiBtnList[j]->floatAbove = TRUE;
				if(event == BUTTON_DOWN && button == LEFT_BUTTON)
				{
					uiBtnList[j]->isClicked = TRUE;
					ButtonEventProcess(BTN_NUM + j);
				} 
				else if(event == BUTTON_UP && button == LEFT_BUTTON)
				{
					uiBtnList[j]->isClicked = FALSE;
				}
			}
			else
			{
				uiBtnList[j]->floatAbove = FALSE;
			}
			printf("");
		}
		updateDisplay(3);
	}
	else
	{
		
		//printf("%lf %lf\n",mouseP->x,GetWindowHeight() - mouseP->y);
		if(isInBound(mouseP))
		{
			for(j = 0; j < BTN_NUM;j++)
			{
				if(isInsideBtn(btnList[j], mouseP->x, mouseP->y))
				{
					btnList[j]->floatAbove = TRUE;
					if(event == BUTTON_DOWN && button == LEFT_BUTTON)
					{
						btnList[j]->isClicked = TRUE;
						ButtonEventProcess(j);
						clickingBtn = TRUE;
						isDragging = FALSE;
					} 
					else if(event == BUTTON_UP && button == LEFT_BUTTON)
					{
						btnList[j]->isClicked = FALSE;
						clickingBtn = FALSE;
					}
				}
				else
				{
					btnList[j]->floatAbove = FALSE;
				}
				printf("");
			}
			updateDisplay(2);
		}
		else
		{
			for(j = 6; j >= 0;j--)
			{
				if(isInside(shpList[j],mouseP))
				{
					shpList[j]->floatAbove = TRUE;
		    		inED = TRUE;
		    	}
		  	    else
		   	    {
		    		shpList[j]->floatAbove = FALSE;
		   		 	inED = FALSE;
				}
				if(event == BUTTON_DOWN && button == LEFT_BUTTON){
					if(inED)
					{
						if(!shpList[j]->isSelected) shpList[j]->isSelected = TRUE; 
						tmpShp = shpList[j];
						for(k = j;k < 6;k++)
						{
							shpList[k] = shpList[k+1];
						}
						shpList[6] = tmpShp;
						isDragging = TRUE;
					}
					else if(!clickingBtn)
					{
	        	        shpList[j]->isSelected = FALSE;
					}
				}
				else if(event == BUTTON_UP && button == LEFT_BUTTON)
				{
					isDragging = FALSE;
				}
				else if(event == BUTTON_DOWN && button == RIGHT_BUTTON)
				{
					if(shpList[6]->isSelected)shpList[6]->rotDeg += 45;
					
				}
				else
				{
					if(isDragging && !((shpList[j]->x >= xCenter * 2 - BOUND_WIDTH) && (mouseP->x - px > 0))
								  && !((shpList[j]->x <= BOUND_WIDTH) && (mouseP->x - px < 0))
								  && !((shpList[j]->y >= yCenter * 2 - BOUND_WIDTH) && (mouseP->y - py > 0))
								  && !((shpList[j]->y <= BOUND_WIDTH) && (mouseP->y - py < 0)))
					{
						shpList[j]->x += mouseP->x-px;
						shpList[j]->y += mouseP->y-py;
					}
					px = mouseP->x;
					py = mouseP->y;
				}
				printf("", isDragging);
			}
			updateDisplay(1);
		}
	}
	
	
	
	//if(test_save)File_in(); 
}

bool isInBound(Point p)
{
	return GetWindowHeight() - p->y < BOUND_WIDTH;
}
void ButtonEventProcess(int btnIndex)
{
	switch(btnIndex){
    case 0  :
       loadGame("");
       break; 
    case 1  :
  		File_in();
       break; 
    case 2  :
       if(shpList[6]->isSelected)shpList[6]->rotDeg += 45;
       updateDisplay(0);
       break; 
    case 3  :
       
       break; 
    case 4  :
	   isInGame = FALSE;
	   
	   cancelTimer(0);
	   Timer(0,TRUE);
	   initUI();
	   
	   break;
	case BTN_NUM:
	   loadGame(pathList[chooseGameIndex]);
	   break;
	case BTN_NUM+1:
		loadGame("");
		break;
	case BTN_NUM+2:
	
		break;
	case BTN_NUM+3:
		ExitGraphics(); 
		break;
	case BTN_NUM+4:
		if(chooseGameIndex > 0)
		{
			chooseGameIndex--;
			initUI();
		} 
		break;
	case BTN_NUM+5:
		if(chooseGameIndex < GAME_NUM - 1)
		{
			chooseGameIndex++;
			initUI();
		} 
		
		break;
	}
}

void DefineColorRGB(string cName, double r,double g,double b)
{
	r /= 256.0;
	g /= 256.0;
	b /= 256.0;
	DefineColor(cName,r,g,b);
}
