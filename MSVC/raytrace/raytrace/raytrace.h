#include <vector>
#include "vector.h"
#include "object.h"
using namespace std;

VECTOR3D raytrace(Ray ray, int depth, vector<object*>* objects, VECTOR3D light);