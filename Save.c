#include "Save.h"
#include "tangramMain.h"
#include "makeShape.h"
#include <windows.h>
#include "finalPattern.h" 
#include "linkedlist.h"

extern Shape shpList[7];
extern linkedlistADT vecList;
extern linkedlistADT disList;
extern double sX,sY;
extern bool isInGame;
int tType,tClr;
double tX,tY,tDeg;
char path[200];

void File_in()
{
	
	OpenConsole();
	gets(path);
	CloseConsole();
	FILE *fp;
	fp=fopen(path, "w");
	
	int i=0;
	for(;i<7;i++)
	{
		fprintf(fp,"%d %lf %lf %lf %d\n",shpList[i]->shapeType,shpList[i]->x,shpList[i]->y,shpList[i]->rotDeg,shpList[i]->colorIndex);
	}
	fprintf(fp,"%lf %lf\n", sX-7,sY-0.7);
	fclose(fp);
	TraverseLinkedList(vecList, putVec);
	
}

void putVec(void *v)
{
	if (v == NULL) return;
	Vect vec = (Vect)v;
	FILE *fp;
	fp=fopen(path, "a");
	fprintf(fp,"%lf %lf\n",vec->deg,vec->len);
	fclose(fp);
}

void loadGame(string pathG)
{
	FILE *fp;
	string tmp;
	//CommDlg_OpenSave_GetFilePath(GetForegroundWindow(),path,500)
	if(strcmp(pathG,"") == 0)
	{
		OpenConsole();
		gets(path);
		CloseConsole();
	}
	else
	{
		strcpy(path,pathG);
	}
	
	fp=fopen(path,"r+");
	int u = 0;
	for(;u < 7; u++)
	{
		tmp = ReadLine(fp);
		sscanf(tmp,"%d %lf %lf %lf %d",&tType,&tX,&tY,&tDeg,&tClr);
		shpList[u] = genShape(tType,tX,tY,tDeg,tClr);
	}
	tmp = ReadLine(fp);
    sscanf(tmp,"%lf %lf",&tX,&tY);
    sX = 8 + tX;
    sY = 1.7 + tY;
    vecList = NewLinkedList();
	while((tmp = ReadLine(fp))!=NULL)
	{
		sscanf(tmp,"%lf %lf",&tX,&tY);
		//printf("%lf %lf ",tX,tY);
		InsertNode(vecList, NULL, genVec(tX,tY));
	}
	fclose(fp);
	initTangrams(TRUE);
	isInGame = TRUE;
	updateDisplay(0);
}

void loadDis(string path)
{
	FILE *fp;
	string tmp;
	fp=fopen(path,"r+");
	int u = 0;
	for(;u < 7; u++) tmp = ReadLine(fp);
	tmp = ReadLine(fp);
	sscanf(tmp,"%lf %lf",&tX,&tY);
    sX = 8 + tX;
    sY = 1.7 + tY;
    disList = NewLinkedList();
	while((tmp = ReadLine(fp))!=NULL)
	{
		sscanf(tmp,"%lf %lf",&tX,&tY);
		InsertNode(disList, NULL, genVec(tX,tY));
	}
	fclose(fp);
	
}
