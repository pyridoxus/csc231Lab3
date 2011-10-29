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

#include <iostream>
using namespace std;
#include <math.h>
#include <GL/glut.h>

void RGBtoHSV();
void HSVtoRGB();

// red, green, blue components (0.0 to 1.0)
float rgb[3] = { 0.f, 0.f, 0.f };

// hue, saturation, value components (0.0 to 1.0)
float hsv[3] = { 0.f, 0.f, 0.f };

void main( int argc, char *argv[] )
{

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

