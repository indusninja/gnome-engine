// Point3.h : Math foundation class to represent a Point in 3D space.

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

#ifndef __Point3_h
#define __Point3_h

class Point3
{
public:
	float x, y, z;

	Point3();
	Point3(float, float, float);
	void Zero();
	void init(Point3);
	void init(float, float, float);
	bool isEqual(Point3 pt);

	Point3 operator*(float factor) const;
	Point3 operator/(float factor) const;
	Point3 operator+(const Point3 &pnt) const;
	Point3 operator-(const Point3 &pnt) const;
	Point3 operator-() const;
	const Point3 &operator*=(float factor);
	const Point3 &operator/=(float factor);
	const Point3 &operator+=(const Point3 &pnt);
	const Point3 &operator-=(const Point3 &pnt);
};

Point3 operator*(float multiple, const Point3 &p);
ostream &operator<<(ostream &output, const Point3 &p);
#endif