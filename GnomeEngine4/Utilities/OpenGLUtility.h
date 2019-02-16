// OpenGLUtility.h : Utility methods used for various OpenGL functionalities.

/* Copyright (c) Prakash Prasad, 2009. */

/* This program is freely distributable without licensing fees 
   and is provided without guarantee or warrantee expressed or 
   implied. This program is -not- in the public domain.

 * Permission to use, copy, modify, and distribute this software for 
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that 
 * the name of Prakash Prasad not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission. 

 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
 * AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL PRAKASH
 * PRASAD  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
 * KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
 * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
 * THIRD PARTIES, WHETHER OR NOT PRAKASH PRASAD HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
 * POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef __OpenGLUtility_h
#define __OpenGLUtility_h

class Color3f
{
public:
	float Red, Green, Blue;

	Color3f();
	Color3f(float R, float G, float B);
	void init(float R, float G, float B);
	void init(Color3f color);
};

int getWindowHeight(void);
int getWindowWidth(void);
bool isFullscreen(void);
UINT getTexture(int index);
void init(int *a, char *b[], const char *title, Camera cam);
void toggleFullScreenMode(void);
void setupLight(float posx, float posy, float posz, float a);
void setupLookAt(float posx, float posy, float posz,
				 float viewx, float viewy, float viewz,
				 float upx, float upy, float upz);
void setupLookAt(Camera cam);
void drawGrid(float y_offset, float gridSize, int colorR, int colorG, int colorB);
void drawArrow(Point3 fulcrum, float rotx, float roty, float rotz);

#endif