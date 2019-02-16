// GameVariables.h : Defines the variables and macros used 
// across the application

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

#ifndef __Variables_h
#define __Variables_h

#define PI							((float)3.141592654f)
#define PI2							((float)6.283185308f)
#define EPSILON2					(float)(1E-2) 
#define EPSILON3					(float)(1E-3) 
#define EPSILON4					(float)(1E-4) 
#define EPSILON5					(float)(1E-5)
#define EPSILON6					(float)(1E-6)
#define DEGREES_TO_RADIANS(ang)		((ang)*PI/180.0)
#define RADIANS_TO_DEGREES(rads)	((rads)*180.0/PI)
#define YROTATE_CEIL				((float)40.0f)
#define BALL_RADIUS					((float)0.02f)
#define CUP_RADIUS					((float)0.05f)
#define GRAVITY						((float)-5.0f)
#define	FRICTION					((float)1.1f)
#define ACCURACY					((int)3)
#define CAMERA_DISTANCE				((float)0.75f)

//const float cameraDistance = 0.5f;
const float arrowMoveStep = 3.0f;
const float powerMultiplier = 5.0f;

#endif