//This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
