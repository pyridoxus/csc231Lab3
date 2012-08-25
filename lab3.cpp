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
/**********************************************************************
Lab 3

Description
-----------
Write a program to change the color of a rectangle by allowing a
user to change both the r,g,b components of the RGB color model
and the h,s,v components of the HSV color model. Use the provided
code to convert RGB to HSV and HSV to RGB.

Instructions
-----------
- Draw a single rectangle in a 2D orthographic view over a grey background
- Change the color of the rectangle by using GLUT keyboard callbacks to allow
  the user to change the r,g,b components (of the RGB color model) and the
	h,s,v components (of the HSV color model) as follows:
    - 'R' key: increases red component of RGB color model
		- 'r' key: decreases red component of RGB color model
    - 'G' key: increases green component of RGB color model
		- 'g' key: decreases green component of RGB color model
		- 'B' key: increases blue component of RGB color model
		- 'b' key: decreases blue component of RGB color model
    - 'H' key: increases hue component of HSV color model
		- 'h' key: decreases hue component of HSV color model
		- 'S' key: increases saturation component of HSV color model
		- 's' key: decreases saturation component of HSV color model
    - 'V' key: increases value component of HSV color model
		- 'v' key: decreases value component of HSV color model
    - 'q' key: quit
    - Print out a menu upon execution to inform the user of choices
- Each time a component value is changed print both the r,g,b and h,s,v
  values of the current color.
**********************************************************************/
#include "lab3.h"

int main( int argc, char *argv[] )
{
	// Show console menu
	consoleMenu();

  // Initialize window system
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
  glutInitWindowSize( 640, 480 );
  glutCreateWindow( "Lab 3" );

  // Initialize graphics
  initDraw();

  // Callbacks
  glutDisplayFunc( drawOrtho );
	glutKeyboardFunc( keyboardCallback );

	// Event loop
  glutMainLoop();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	return 0;
}

// Orthographic draw
void drawOrtho(void)
{
  glClearColor(0.5, 0.5, 0.5, 1);
  glClear( GL_COLOR_BUFFER_BIT );

  glColor3f(rgb[0], rgb[1], rgb[2]);
	glBegin(GL_POLYGON);
	glVertex2i( -5, -5);
	glVertex2i( -5, 5);
	glVertex2i( 5, 5);
	glVertex2i( 5, -5);
	glEnd();
	glFlush();
}

// RGB to HSV color space conversion (uses global rgb and hsv arrays)
void RGBtoHSV()
{
  float m;
  float r1, g1, b1;
  float r = rgb[0];
  float g = rgb[1];
  float b = rgb[2];
  hsv[0]=0.f;
  hsv[1]=0.f;
  hsv[2]=0.f;
  hsv[2] = max(r,g);
  hsv[2] = max(hsv[2],b);
  m = min(r,g);
  m = min(m,b);
  if(hsv[2]==0.f)
    hsv[1] = 0.f;
  else
    hsv[1] = (hsv[2]-m)/hsv[2];
  if(hsv[1]==0.f)
    hsv[0] = 0.f;
  else
    {
      r1 = (hsv[2] - r) / (hsv[2] - m);
      g1 = (hsv[2] - g) / (hsv[2] - m);
      b1 = (hsv[2] - b) / (hsv[2] - m);
      if(r == hsv[2])
        hsv[0] = b1 - g1;
      if(g == hsv[2])
        hsv[0] = 2.0 + r1 - b1;
      if(b == hsv[2])
        hsv[0] = 4.0 + g1 - r1;
      hsv[0] *= 60.0;
      if(hsv[0] < 0.0)
        hsv[0] += 360.0;
      hsv[0] /= 360.0;
    }
}

// HSV to RGB color space conversion (uses global rgb and hsv arrays)
void HSVtoRGB()
{
  float i,f,p,q,t;              // temporary storage for float
  float r,g,b;                  // floating point rgb
  float h,s,v;                  // hsv components

  // convert hue to degrees
  h = hsv[0]*360.0;
  s = hsv[1];
  v = hsv[2];
  if(s == 0.0)
    {
      r = v;
      g = v;
      b = v;
    }
  else
    {
      if(h == 360.0)
        h = 0.0;
      else
        h /= 60.0;
      i = (float)floor(h);
      f = h - i;
      p = v * ((float)1.0 - s);
      q = v * ((float)1.0 - (s * f));
      t = v * ((float)1.0 - (s * ((float)1.0 - f)));
      switch((int)i)
        {
        case 0:
          r = v; g = t; b = p;
          break;
        case 1:
          r = q; g = v; b = p;
          break;
        case 2:
          r = p; g = v; b = t;
          break;
        case 3:
          r = p; g = q; b = v;
          break;
        case 4:
          r = t; g = p; b = v;
          break;
        case 5:
          r = v;
          g = p;
          b = q;
        }
    }
  rgb[0] = r;
  rgb[1] = g;
  rgb[2] = b;
}

void consoleMenu(void)
{
	cout << "- 'R' key: increases red component of RGB color model" << endl;
	cout << "- 'r' key: decreases red component of RGB color model" << endl;
	cout << "- 'G' key: increases green component of RGB color model" << endl;
	cout << "- 'g' key: decreases green component of RGB color model" << endl;
	cout << "- 'B' key: increases blue component of RGB color model" << endl;
	cout << "- 'b' key: decreases blue component of RGB color model" << endl;
	cout << "- 'H' key: increases hue component of HSV color model" << endl;
	cout << "- 'h' key: decreases hue component of HSV color model" << endl;
	cout << "- 'S' key: increases saturation component of HSV color model" << endl;
	cout << "- 's' key: decreases saturation component of HSV color model" << endl;
	cout << "- 'V' key: increases value component of HSV color model" << endl;
	cout << "- 'v' key: decreases value component of HSV color model" << endl;
	cout << "- 'q' key: quit" << endl;
	return;
}

void keyboardCallback(unsigned char key, int x, int y)
{
	int i;
	switch(key)
	{
		case 'R':
			rgb[0] += 0.1;
		break;
		case 'r':
			rgb[0] -= 0.1;
		break;
		case 'G':
			rgb[1] += 0.1;
		break;
		case 'g':
			rgb[1] -= 0.1;
		break;
		case 'B':
			rgb[2] += 0.1;
		break;
		case 'b':
			rgb[2] -= 0.1;
		break;
		case 'H':
			hsv[0] += 0.1;
		break;
		case 'h':
			hsv[0] -= 0.1;
		break;
		case 'S':
			hsv[1] += 0.1;
		break;
		case 's':
			hsv[1] -= 0.1;
		break;
		case 'V':
			hsv[2] += 0.1;
		break;
		case 'v':
			hsv[2] -= 0.1;
		break;
		case 'q':
			exit(0);
	}
	for(i = 0; i < 3; i++)
	{
		if(rgb[i] < 0.0) rgb[i] = 0.0;
		if(rgb[i] > 1.0) rgb[i] = 1.0;
		if(hsv[i] < 0.0) hsv[i] = 0.0;
		if(hsv[i] > 1.0) hsv[i] = 1.0;
	}
	for(i = 0; i < 6; i++)
	{
		if(key == RGBActionList[i])
		{
			RGBtoHSV();
			break;
		}
	}
	for(i = 0; i < 6; i++)
	{
		if(key == HSVActionList[i])
		{
			HSVtoRGB();
			break;
		}
	}
	glutPostRedisplay();
	return;
}

// Initialize drawing
void initDraw(void)
{
  // Background color
  glClearColor(0.0, 0.0, 0.0, 1.0);

  // 2D world projection
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluOrtho2D( -10.0, 10.0, -10.0, 10.0 );
}
