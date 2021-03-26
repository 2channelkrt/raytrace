#include "raytrace.h"
#include <cstdio>
#define LIMIT 90000
VECTOR3D raytrace(Ray ray, int depth, vector<object*>* objects, VECTOR3D light)
{
	float min_t = LIMIT;

	object* o = nullptr;
	for (int i = 0; i < objects->size(); i++)
	{
		float t;
		object* obj = objects->at(i);

		if (obj->hit(ray, &t))
		{
			if (t <= min_t)
			{
				min_t = t;//min_t is distance of the light hit
				o = obj;//o is object that light hit
			}
		}
	}
	//printf("min_t: %f\n", min_t);
	if (min_t == LIMIT)//when nothing is hit
	{
		return VECTOR3D(0, 0, 0);//sky color
	}
	///////////////////////////////////////////shadow
	float shadow = 1.0;
	float min_st = LIMIT;

	VECTOR3D point = ray.position(min_t);
	/////////temporary light
	VECTOR3D lightRay = light - point;
	lightRay.Normalized();

	Ray shadow_ray(point, lightRay);

	for (int i = 0; i < objects->size(); i++)
	{
		float t;
		object* obj = objects->at(i);

		if (obj->hit(shadow_ray, &t))
		{
			if (t <= min_st)
			{
				min_st = t;
			}
		}
	}
	if (min_st == LIMIT) shadow = 1, 0;
	else shadow = 0.4f;

	////////////////////////////////////calculate intensity and color
	if (depth > 0)
	{
		
		return o->k_ambient + (o->getColor(point, light, ray.origin)) * shadow\
			+ raytrace(Ray(point, o->get_reflection(point, light)), depth - 1, objects, light) * 0.8\
			;// +raytrace(Ray(point, Refraction), depth - 1, objects)*0.3;
	}
	else
	{
		return o->k_ambient + (o->getColor(point, light, ray.origin)) * (shadow + 0.3);
	}
}