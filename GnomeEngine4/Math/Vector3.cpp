#include "..\Misc\stdafx.h"

Vector3::Vector3()
{
	this->Zero();
}

Vector3::Vector3(float x, float y, float z)
{
	this->init(x, y, z);
}

Vector3::Vector3(Point3 pt)
{
	this->init(pt.x, pt.y, pt.z);
}

void Vector3::init(Point3 pt1, Point3 pt2)
{
	this->init(pt2.x - pt1.x,
			   pt2.y - pt1.y,
			   pt2.z - pt1.z); // Build a Vector directed from pt1 to pt2
}

void Vector3::init(Vector3 vec)
{
	this->init(vec.x, vec.y, vec.z);
	this->isNormalized = false;
}

void Vector3::init(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->isNormalized = false;
}

void Vector3::Zero()
{
	this->x = this->y = this->z = 0.0f;
	this->isNormalized = false;
}

Vector3 Vector3::operator*(float factor) const
{
	return Vector3(x * factor, y * factor, z * factor);
}

Vector3 Vector3::operator/(float factor) const
{
	return Vector3(x / factor, y / factor, z / factor);
}

Vector3 Vector3::operator+(const Vector3& vec) const
{
	return Vector3(x + vec.x, y + vec.y, z + vec.z);
}

Vector3 Vector3::operator-(const Vector3& vec) const
{
	return Vector3(x - vec.x, y - vec.y, z - vec.z);
}

Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

const Vector3& Vector3::operator*=(float factor)
{
	x *= factor;
	y *= factor;
	z *= factor;
	return *this;
}

const Vector3& Vector3::operator/=(float factor)
{
	x /= factor;
	y /= factor;
	z /= factor;
	return *this;
}

const Vector3& Vector3::operator+=(const Vector3& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
	return *this;
}

const Vector3& Vector3::operator-=(const Vector3& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	return *this;
}

void Vector3::Add(Vector3 vec)
{
	this->x += vec.x;
	this->y += vec.y;
	this->z += vec.z;
	this->isNormalized = false;
}

void Vector3::Subtract(Vector3 vec)
{
	this->x += vec.x;
	this->y += vec.y;
	this->z += vec.z;
	this->isNormalized = false;
}

void Vector3::ScalarMultiply(float k)
{
	this->x *= k;
	this->y *= k;
	this->z *= k;
	this->isNormalized = false;
}

void Vector3::Reverse(void)
{
	this->ScalarMultiply(-1.0f);
}

void Vector3::RotateX(float radx)
{
	float cosRadX = cos(radx), sinRadX = sin(radx);
	float valX = this->x;
	float valY = (this->y * cosRadX) - (this->z * sinRadX);
	float valZ = (this->y * sinRadX) + (this->z * cosRadX);
	this->init(valX, valY, valZ);
}

void Vector3::RotateY(float rady)
{
	float cosRadY = cos(rady), sinRadY = sin(rady);
	float valX = (this->x * cosRadY) + (this->z * sinRadY);
	float valY = this->y;
	float valZ = -(this->x * sinRadY) + (this->z * cosRadY);
	this->init(valX, valY, valZ);
}

void Vector3::RotateZ(float radz)
{
	float cosRadZ = cos(radz), sinRadZ = sin(radz);
	float valX = (this->x * cosRadZ) - (this->y * sinRadZ);
	float valY = (this->x * sinRadZ) + (this->y * cosRadZ);
	float valZ = this->z;
	this->init(valX, valY, valZ);
}

float Vector3::DotProduct(Vector3 vec)
{
	return ((this->x * vec.x) + (this->y * vec.y) + (this->z * vec.z));
}

void Vector3::CrossProduct(Vector3 vec)
{
	float a, b, c;
	a = ((this->y * vec.z) - (this->z * vec.y));
	b = -((this->x * vec.z) - (this->z * vec.x));
	c = ((this->x * vec.y) - (this->y * vec.x));
	this->x = a;
	this->y = b;
	this->z = c;
	this->isNormalized = false;
}

void Vector3::CrossProduct(Vector3 vec, Vector3* result)
{
	result->x = ((this->y * vec.z) - (this->z * vec.y));
	result->y = -((this->x * vec.z) - (this->z * vec.x));
	result->z = ((this->x * vec.y) - (this->y * vec.x));
	result->isNormalized = false;
}

float Vector3::Length(void)
{
	return (
	  (float)sqrtf(this->x * this->x + this->y * this->y + this->z * this->z));
}

void Vector3::Normalize(void)
{
	if (this->isNormalized)
		return;

	float factor = this->Length();
	if (factor < EPSILON5)
		return;
	this->ScalarMultiply(1.0f / factor);
	this->isNormalized = true;
}

float Vector3::CosTheta(Vector3 vec)
{
	return (
	  this->DotProduct(vec) /
	  (this->Length() * vec.Length())); // this function returns the cosine of
										// the angle between two vectors.
}

void Vector3::Projection(Vector3 u)
{
	float k = u.DotProduct(*this);
	k /= (float)powf(u.Length(), 2);
	this->x = k * u.x;
	this->y = k * u.y;
	this->z = k * u.z;
	this->isNormalized = false;
}

void Vector3::Projection(Vector3 u, Vector3* result)
{
	float k = u.DotProduct(*this);
	k /= (float)powf(u.Length(), 2);
	result->x = k * u.x;
	result->y = k * u.y;
	result->z = k * u.z;
	result->isNormalized = false;
}

// getFaceNormal() will calculate the normal for any face given three points in
// anti-clockwise order
void Vector3::getFaceNormal(Point3 pointa, Point3 pointb, Point3 pointc)
{
	Vector3 vector1(
	  pointa.x - pointb.x, pointa.y - pointb.y, pointa.z - pointb.z);
	Vector3 vector2(
	  pointc.x - pointb.x, pointc.y - pointb.y, pointc.z - pointb.z);
	vector2.CrossProduct(vector1,
						 this); // calculates vector at 90° to to 2 vectors
	this->Normalize();			// makes the vector length 1
}

// Calculate collision resultant vector by formula R= 2*(-I dot N)*N + I
void Vector3::getReflectionVector(Vector3 normalVector)
{
	Vector3 firstFactor(
	  this->x, this->y, this->z); // firstFactor = Reflect(i.e this) = I
	firstFactor.Reverse();		  // firstFactor = -I
	float multiple =
	  2 * firstFactor.DotProduct(normalVector); // multiple = 2*(-I dot N)
	normalVector.ScalarMultiply(multiple);		// N = 2*(-I dot N)*N
	this->Add(normalVector); // R = N + I = 2*(-I dot N)*N + I
}

Vector3 operator*(float multiple, const Vector3& v)
{
	return (v * multiple);
}

ostream& operator<<(ostream& output, const Vector3& v)
{
	output << '(' << v.x << "i, " << v.y << "j, " << v.z << "k)";
	return output;
}
