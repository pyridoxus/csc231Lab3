#ifndef LAB3_H_
#define LAB3_H_


#include <iostream>
using namespace std;
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>

void RGBtoHSV(void);
void HSVtoRGB(void);
void consoleMenu(void);
void drawOrtho(void);
void keyboardCallback(unsigned char key, int x, int y);
void initDraw(void);

// red, green, blue components (0.0 to 1.0)
float rgb[3] = { 0.f, 0.f, 0.f };

// hue, saturation, value components (0.0 to 1.0)
float hsv[3] = { 0.f, 0.f, 0.f };

// RGB to HSV keyboard action list
char RGBActionList[7] = "RrGgBb";

// HSV to RGB keyboard action list
char HSVActionList[7] = "HhSsVv";

#endif
