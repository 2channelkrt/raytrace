#pragma once
#include "vector.h"

class rotateVec
{
public:
	rotateVec()
	{
		this->axi.x = 0.0f;
		this->axi.y = 0.0f;
		this->axi.z = 0.0f;
		this->angle = 0.0f;
	}

	rotateVec(float x, float y, float z, float angle)
	{
		this->axi.x = x;
		this->axi.y = y;
		this->axi.z = z;
		this->angle = angle;
	}

	rotateVec(VECTOR3D v, float angle)
	{
		this->axi = v;
		this->angle = angle;
	}


	VECTOR3D axi;
	float angle;
};