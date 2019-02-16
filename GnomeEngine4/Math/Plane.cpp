#include "..\Misc\stdafx.h"

void Plane::init(Point3 pt, Vector3 n)
{
	this->pointInPlane.init(pt);
	this->normal.init(n);
	if (!n.isNormalized)
		this->normal.Normalize();
}

float Plane::ComputePointPlaneHalfSpace(Point3 pt)
{
	// test if a point in on the plane
	// in the +ive halfspace the value returned is +ive
	// or in the -ive halfspace the value returned is -ive
	float value = this->normal.x * (pt.x - this->pointInPlane.x) +
				  this->normal.y * (pt.y - this->pointInPlane.y) +
				  this->normal.z * (pt.z - this->pointInPlane.z);

	return value;
}

float Plane::ComputeSafeYonPlane(float ptx, float ptz)
{
	float pty = (-this->normal.x * (ptx - this->pointInPlane.x) -
				 this->normal.z * (ptz - this->pointInPlane.z) +
				 this->normal.y * this->pointInPlane.y) /
				this->normal.y;

	return pty;
}
