// Physics.h : 

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

#ifndef __Physics_h
#define __Physics_h

void BallToFloorCollision(Point3 &ballPosition, Vector3 &ballVelocity, Vector3 &ballAcceleration, Plane floorPlane, float ballRadius, float gravity);
int BallToWallCollision(Point3 &ballPosition, Vector3 &ballVelocity, Vector3 &ballAcceleration, Plane wallPlane, float ballRadius, int neighbour);
bool BallToHoleCollision(Point3 &holePosition, Point3 &ballPosition, Vector3 &ballVelocity, Vector3 &ballAcceleration);
bool BallToBallCollision(Point3 &ballPosition1, Point3 &ballPosition2, float ballRadius);

#endif