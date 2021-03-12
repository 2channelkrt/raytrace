#pragma once
#include "quat.h"

QUAT AxiToQuat(rotateVec vec);
rotateVec QuatToAxi(QUAT q);
float min(float a, float b);
float max(float a, float b);