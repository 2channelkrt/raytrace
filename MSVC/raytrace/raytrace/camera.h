#include "vector.h"

class Camera
{
public:
	Camera()
	{
		this->position.x = 0;
		this->position.y = 60;
		this->position.z = 30;

		this->direction.x = 0;
		this->direction.y = 0;
		this->direction.z = 30;

		this->top.x = 0;
		this->top.y = 0;
		this->top.z = 1;
	}
	VECTOR3D position;
	VECTOR3D direction; //magnitude should always be 1
	VECTOR3D top;
};
