#ifndef __TGUI_H__
#define __TGUI_H__

typedef struct {
	double top, left;
    double width, height;
    bool isShow;
    bool floatAbove;
    bool isClicked;
    string label;
    int fontSize;
} *Button;

Button genBtn(double top,double left,double width,double height,string label,int fontSize);
void renderBtn(Button btn);
bool isInsideBtn(Button btn, double x, double y);

#endif 

