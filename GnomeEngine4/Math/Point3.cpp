#include "..\Misc\stdafx.h"

Point3::Point3()
{
	this->Zero();
}

Point3::Point3(float x, float y, float z)
{
	this->init(x, y, z);
}

void Point3::Zero()
{
	this->x = this->y = this->z = 0.0f;
}

void Point3::init(Point3 pt)
{
	this->init(pt.x, pt.y, pt.z);
}

void Point3::init(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

bool Point3::isEqual(Point3 pt)
{
	float val1 = (x * x) + (y * y) + (z * z);
	float val2 = (pt.x * pt.x) + (pt.y * pt.y) + (pt.z * pt.z);
	if ((val1 >= (val2 - EPSILON4)) && (val1 <= (val2 + EPSILON4)))
		return true;
	else
		return false;
}

Point3 Point3::operator*(float factor) const
{
	return Point3(x * factor, y * factor, z * factor);
}

Point3 Point3::operator/(float factor) const
{
	return Point3(x / factor, y / factor, z / factor);
}

Point3 Point3::operator+(const Point3& pnt) const
{
	return Point3(x + pnt.x, y + pnt.y, z + pnt.z);
}

Point3 Point3::operator-(const Point3& pnt) const
{
	return Point3(x - pnt.x, y - pnt.y, z - pnt.z);
}

Point3 Point3::operator-() const
{
	return Point3(-x, -y, -z);
}

const Point3& Point3::operator*=(float factor)
{
	x *= factor;
	y *= factor;
	z *= factor;
	return *this;
}

const Point3& Point3::operator/=(float factor)
{
	x /= factor;
	y /= factor;
	z /= factor;
	return *this;
}

const Point3& Point3::operator+=(const Point3& pnt)
{
	x += pnt.x;
	y += pnt.y;
	z += pnt.z;
	return *this;
}

const Point3& Point3::operator-=(const Point3& pnt)
{
	x -= pnt.x;
	y -= pnt.y;
	z -= pnt.z;
	return *this;
}

Point3 operator*(float multiple, const Point3& p)
{
	return p * multiple;
}

ostream& operator<<(ostream& output, const Point3& p)
{
	output << '(' << p.x << ", " << p.y << ", " << p.z << ')';
	return output;
}
