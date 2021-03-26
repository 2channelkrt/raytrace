#pragma once
#include "rotateVec.h"
class QUAT
{
public:
	QUAT()
		:w(0.0f), x(0.0f), y(0.0f), z(0.0f) {}

	QUAT(float w, float x, float y, float z)
		:w(w), x(x), y(y), z(z) {}

	QUAT operator*(QUAT q);
	QUAT& operator*=(QUAT q);

	float w, x, y, z;
};