#pragma once

#include "quat.h"

QUAT AxiToQuat(rotateVec vec)
{
	QUAT res;
	float a = vec.angle / 2.0;
	res.w = cos(a);
	res.x = vec.axi.x * sin(a);
	res.y = vec.axi.y * sin(a);
	res.z = vec.axi.z * sin(a);
	return res;
}

rotateVec QuatToAxi(QUAT q)
{
	rotateVec res;
	float temp = sqrt(1 - q.w * q.w);
	res.angle = 2 * acos(q.w);
	res.axi.x = q.x / temp;
	res.axi.y = q.y / temp;
	res.axi.z = q.z / temp;
	return res;
}

QUAT QUAT::operator*(QUAT q)
{
	QUAT res;
	float A, B, C, D, E, F, G, H;

	A = (w + x) * (q.w + q.x);
	B = (z - y) * (q.y - q.z);
	C = (w - x) * (q.y + q.z);
	D = (y + z) * (q.w - q.x);
	E = (x + z) * (q.x + q.y);
	F = (x - z) * (q.x - q.y);
	G = (w + y) * (q.w - q.z);
	H = (w - y) * (q.w + q.z);

	res.w = B + (-E - F + G + H) / 2;
	res.x = A - (E + F + G + H) / 2;
	res.y = C + (E - F + G - H) / 2;
	res.z = D + (E - F - G + H) / 2;

	return res;
}

QUAT& QUAT::operator*=(QUAT q)
{
	*this = *this * q;
	return *this;
}

float VECTOR3D::Magnitude()
{
	return sqrt(x * x + y * y + z * z);
}

float VECTOR3D::InnerProduct(VECTOR3D v)
{
	return (x * v.x + y * v.y + z * v.z);
}

VECTOR3D VECTOR3D::CrossProduct(VECTOR3D v)
{
	VECTOR3D result;
	result.x = y * v.z - z * v.y;
	result.y = z * v.x - x * v.z;
	result.z = x * v.y - y * v.x;

	return result;
}

VECTOR3D& VECTOR3D::Normalized()
{
	float w = Magnitude();
	if (w < 0.00001) return *this;
	this->x /= w;
	this->y /= w;
	this->z /= w;
	return *this;
}

VECTOR3D VECTOR3D::operator+(VECTOR3D v)
{
	VECTOR3D result = (*this);
	result.x += v.x;
	result.y += v.y;
	result.z += v.z;

	return result;
}

VECTOR3D& VECTOR3D::operator+=(VECTOR3D v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}

VECTOR3D VECTOR3D::operator-(VECTOR3D v)
{
	VECTOR3D result = (*this);
	result.x -= v.x;
	result.y -= v.y;
	result.z -= v.z;

	return result;
}
VECTOR3D& VECTOR3D::operator-=(VECTOR3D v)
{
	*this = *this - v;
	return *this;
}

VECTOR3D VECTOR3D::operator*(float val)
{
	VECTOR3D result = (*this);
	result.x *= val;
	result.y *= val;
	result.z *= val;

	return result;
}

VECTOR3D& VECTOR3D::operator*=(float val)
{
	*this = *this * val;
	return *this;
}

VECTOR3D VECTOR3D::operator/(float val)
{
	VECTOR3D result = (*this);
	result.x /= val;
	result.y /= val;
	result.z /= val;

	return result;
}

VECTOR3D& VECTOR3D::operator/=(float val)
{
	this->x /= val;
	this->y /= val;
	this->z /= val;

	return *this;
}

VECTOR3D& VECTOR3D::operator-=(float val)
{
	this->x -= val;
	this->y -= val;
	this->z -= val;
	return *this;
}

VECTOR3D& VECTOR3D::operator+=(float val)
{
	this->x += val;
	this->y += val;
	this->z += val;
	return *this;
}

float min(float a, float b)
{
	return a > b ? b : a;
}
float max(float a, float b)
{
	return a > b ? a : b;
}
VECTOR3D Ray::position(float mul)
{
	return this->origin + this->dir * mul;
}