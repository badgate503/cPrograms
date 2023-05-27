#include <time.h>
#include "timer.h"
#include "extgraph.h"
#include "strlib.h"

void Timer(double maxT, bool isStop)
{
	static double start,stop=0;
	clock_t tmp;
	static bool isStart=TRUE;
	if(isStop)
	{
		start = 0;
		stop = 0;
		isStart = TRUE;
	}
	tmp=clock();
	if(isStart)
	{
		start=(double)tmp/CLK_TCK;
		isStart=FALSE;
	}
	else
	{
		stop=(double)tmp/CLK_TCK;
	}
	
	if(!isStart && (stop-start) >= maxT)
	{
		OpenConsole();
		printf("时间到！游戏结束\n");
		system("pause");
		CloseConsole();
		ExitGraphics();
	}
	
	int M,S,printM,printS,maxM,maxS;
	maxM=((int)maxT)/60;
	maxS=((int)maxT)%60;
	
	double dt= stop-start>=0 ? stop-start : 0;
	M=((int)dt)/60;
	S=((int)dt)%60;
	if(maxS-S < 0){
		printS=maxS-S+60;
		maxM--;
		printM=maxM-M;
	}else{
		printS=maxS-S;
		printM=maxM-M;
	}
	
	string timeStr;
	timeStr=TimeToString(printM,printS);
	SetPointSize(50); 
	double x,y;
	x=GetWindowWidth() * 0.8;
	y=GetWindowHeight() * 0.95;
	SetPenColor("Black");
	EraseTime(x,y);
	MovePen(x,y);
	
	DrawTextString(timeStr);
}

string TimeToString(int m,int s)
{
	string str,Mstr,Sstr;
	
	if(m == 0){
		Mstr=CopyString("00");
		if(s == 0){
			Sstr=CopyString("00");
		}else if(s < 10){
			Sstr=Concat("0",IntegerToString(s));
		}else{
			Sstr=CopyString(IntegerToString(s));
		}
	}else if(m < 10){
		Mstr=Concat("0",IntegerToString(m));
		if(s == 0){
			Sstr=CopyString("00");
		}else if(s < 10){
			Sstr=Concat("0",IntegerToString(s));
		}else{
			Sstr=IntegerToString(s);
		}
	}else{
		Mstr=IntegerToString(m);
		if(s == 0){
			Sstr=CopyString("00");
		}else if(s < 10){
			Sstr=Concat("0",IntegerToString(s));
		}else{
			Sstr=IntegerToString(s);
		}
	}
	str=Concat(Mstr,":");
	str=Concat(str,Sstr);
	return str;
}

void EraseTime(double x,double y)
{
	SetEraseMode(TRUE);
	MovePen(x,y);
	DrawTextString("00:00");
	int i=1;
	string allNumber,numberStr;
	for(;i<=9;i++){
		MovePen(x,y);
		int n=i+i*10;
		numberStr=IntegerToString(n);
		allNumber=Concat(numberStr,":");
		allNumber=Concat(allNumber,numberStr);
		DrawTextString(allNumber);
	}
	SetEraseMode(FALSE);
}
