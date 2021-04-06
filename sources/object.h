#pragma once
#include "include/GL/freeglut.h"
#include "vector.h"
class object
{
public:
	VECTOR3D k_ambient;
	VECTOR3D k_diffuse;
	VECTOR3D k_specular;
	float k_shineness;

	object() {}

	virtual ~object() {}
	void setMaterial(const char* material);
	virtual bool hit(Ray r, float* t) = 0;
	virtual VECTOR3D getColor(VECTOR3D point, VECTOR3D light, VECTOR3D ray) = 0;
	virtual VECTOR3D get_normal(VECTOR3D point) = 0;
	virtual VECTOR3D get_reflection(VECTOR3D point, VECTOR3D light) = 0;
};
class sphere :public object
{
public:
	sphere(VECTOR3D center, float radius, const char* material)
	{
		setMaterial(material);


		this->center = center;
		this->radius = radius;
	}
	virtual bool hit(Ray r, float* t);
	virtual VECTOR3D getColor(VECTOR3D point, VECTOR3D light, VECTOR3D ray_origin);
	virtual VECTOR3D get_normal(VECTOR3D point);
	virtual VECTOR3D get_reflection(VECTOR3D point, VECTOR3D light);
	VECTOR3D center;
	float radius;
};
class plane :public object
{
public:
	plane(float Loc, VECTOR3D normal, const char dir, const char* material)
	{
		setMaterial(material);
		this->a = Loc;
		this->normalDirection = dir;
		this->normal = normal;
	}
	virtual bool hit(Ray r, float* t);
	virtual VECTOR3D getColor(VECTOR3D point, VECTOR3D light, VECTOR3D ray_origin);
	virtual VECTOR3D get_normal(VECTOR3D point);
	virtual VECTOR3D get_reflection(VECTOR3D point, VECTOR3D light);
	float a;
	char normalDirection;
	VECTOR3D normal;
};
class triangle :public object
{
public:
	triangle(VECTOR3D a,VECTOR3D b, VECTOR3D c, const char* material)//should be given in cw. Noraml will be calculated as is.
	{
		setMaterial(material);
		this->a=a;
		this->b=b;
		this->c=c;
		this->normal=compute_normal();
	}
	VECTOR3D compute_normal();
	VECTOR3D a,b,c;
	VECTOR3D normal;
};
