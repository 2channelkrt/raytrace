#pragma once

#include <cmath>
#include <cstdio>
class VECTOR3D
{
public:

	VECTOR3D()
		:x(0.0f), y(0.0f), z(0.0f) {}

	VECTOR3D(float x, float y, float z)
		:x(x), y(y), z(z) {}

	void print()
	{
		printf("%f %f %f\n", x, y, z);
	}

	float Magnitude();
	float InnerProduct(VECTOR3D v);
	VECTOR3D CrossProduct(VECTOR3D v);
	VECTOR3D& Normalized();

	VECTOR3D operator+(VECTOR3D v);
	VECTOR3D& operator+=(VECTOR3D v);

	VECTOR3D operator-(VECTOR3D v);
	VECTOR3D& operator-=(VECTOR3D v);

	VECTOR3D operator*(float val);
	VECTOR3D& operator*=(float val);

	VECTOR3D operator/(float val);
	VECTOR3D& operator/=(float val);

	VECTOR3D& operator-=(float val);
	VECTOR3D& operator+=(float val);

	float x;
	float y;
	float z;
};

class Ray
{
public:
	Ray(VECTOR3D origin, VECTOR3D dir)
	{
		static int i = 0;
		i++;
		if(i%100000==0) //if this line doesn't exist, memory violation. Why?
		//printf("%f\n", this);
		this->origin = origin;
		this->dir = dir.Normalized();
	}
	Ray()
	{

	}
	VECTOR3D position(float mul);
	VECTOR3D origin, dir;
};
#pragma once
