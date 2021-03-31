#include <string.h>
#include "GL/freeglut.h"
#include "object.h"
#include "functions.h"
#include "stdio.h"

bool plane::hit(Ray r, float* t)
{
	r.dir.Normalized();
	float d;
	if (normalDirection == 'x')
		d = (this->a - r.origin.x) / r.dir.x;
	else if (normalDirection == 'y')
		d = (this->a - r.origin.y) / r.dir.y;
	else if (normalDirection == 'z')
		d = (this->a - r.origin.z) / r.dir.z;
	else printf("something wrong with directon\n");

	if (d < 0.01)
	{
		*t = 10000.0;
		return false;
	}
	*t = d;
	return true;
}
bool sphere::hit(Ray r, float* t)
{
	r.dir.Normalized();
	float b = 2.0 * (r.dir.InnerProduct(r.origin - this->center));
	float c = pow((r.origin - this->center).Magnitude(), 2) - pow(this->radius, 2);

	float d = pow(b, 2) - (4.0 * c);

	if (d < 0.0)
	{
		*t = 10000.0;
		return false;
	}
	else if (d == 0.0)
	{
		*t = (-1.0) * b / 2.0;
		if (*t > 0.01) return true;
		else return false;
	}
	else
	{
		float t1 = ((-1.0) * b - sqrt(d)) / 2.0;
		float t2 = ((-1.0) * b + sqrt(d)) / 2.0;

		if (t1 > 0.01 && t2 > 0.01)
		{
			*t = (t1 < t2) ? t1 : t2;
			return true;
		}
		else return false;
	}
}

VECTOR3D sphere::getColor(VECTOR3D point, VECTOR3D light, VECTOR3D ray_origin)
{
	VECTOR3D pointNormal = get_normal(point); //normal
	pointNormal.Normalized();
	VECTOR3D inputRay = ray_origin - point;//ray
	inputRay.Normalized();
	VECTOR3D lightRay = light - point;//�Ի籤
	lightRay.Normalized();
	VECTOR3D reflectRay = lightRay * (-1.0) + pointNormal * (lightRay.InnerProduct(pointNormal)) * 2.0;
	//VECTOR3D reflectRay = get_reflection(point, light);
	float diffuse = max((float)0.0, pointNormal.InnerProduct(lightRay));
	float specular = pow(max((float)0.0, inputRay.InnerProduct(reflectRay.Normalized())), k_shineness);

	return this->k_diffuse * diffuse + this->k_specular * specular;
}
VECTOR3D plane::getColor(VECTOR3D point, VECTOR3D light, VECTOR3D ray_origin)
{
	VECTOR3D pointNormal = get_normal(point);
	pointNormal.Normalized();
	VECTOR3D inputRay = ray_origin - point;
	inputRay.Normalized();
	VECTOR3D lightRay = light - point;
	lightRay.Normalized();

	VECTOR3D reflectRay = lightRay * (-1.0) + pointNormal * (lightRay.InnerProduct(pointNormal)) * 2.0;
	//VECTOR3D reflectRay = get_reflection(point, light);
	float diffuse = max((float)0.0, pointNormal.InnerProduct(lightRay));
	float specular = pow(max((float)0.0, inputRay.InnerProduct(reflectRay.Normalized())), k_shineness);

	return this->k_diffuse * diffuse + this->k_specular * specular;
}

VECTOR3D sphere::get_normal(VECTOR3D point)
{
	return (point - center).Normalized();
}
VECTOR3D plane::get_normal(VECTOR3D point)
{
	return this->normal.Normalized();
}
VECTOR3D sphere::get_reflection(VECTOR3D point, VECTOR3D light)
{
	return ((light - point).Normalized() * (-1.0) + get_normal(point).Normalized() * ((light - point).Normalized().InnerProduct(get_normal(point).Normalized())) * 2.0).Normalized();
}
VECTOR3D plane::get_reflection(VECTOR3D point, VECTOR3D light)
{
	return ((light - point).Normalized() * (-1.0) + get_normal(point) * ((light - point).Normalized().InnerProduct(get_normal(point))) * 2.0).Normalized();
}
VECTOR3D triangle::compute_normal()
{
	VECTOR3D temp(0,0,0);
	return temp;
}


void object::setMaterial(const char* material)
{
	if (strcmp(material,"Gold")==0)
	{
		this->k_ambient.x = 0.24725;
		this->k_ambient.y = 0.1995;
		this->k_ambient.z = 0.0745;


		this->k_diffuse.x = 0.75164;
		this->k_diffuse.y = 0.60648;
		this->k_diffuse.z = 0.22648;

		this->k_specular.x = 0.628281;
		this->k_specular.y = 0.666862;
		this->k_specular.z = 0.366065;

		this->k_shineness = 51.2;
	}
	else if (strcmp(material,"Cyan")==0)
	{
		this->k_ambient.x = 0.0f;
		this->k_ambient.y = 0.05f;
		this->k_ambient.z = 0.05f;

		this->k_diffuse.x = 0.4;
		this->k_diffuse.y = 0.5;
		this->k_diffuse.z = 0.5;

		this->k_specular.x = 0.04;
		this->k_specular.y = 0.7;
		this->k_specular.z = 0.7;

		this->k_shineness = 10.0f;
	}
	else if (strcmp(material,"White")==0)
	{
		this->k_ambient.x = 0.0f;
		this->k_ambient.y = 0.0f;
		this->k_ambient.z = 0.0f;


		this->k_diffuse.x = 0.55;
		this->k_diffuse.y = 0.55;
		this->k_diffuse.z = 0.55;

		this->k_specular.x = 0.7;
		this->k_specular.y = 0.7;
		this->k_specular.z = 0.7;

		this->k_shineness = 32.0f;
	}
	else if (strcmp(material,"WhiteRubber")==0)
	{
		this->k_ambient.x = 0.05f;
		this->k_ambient.y = 0.05f;
		this->k_ambient.z = 0.05f;


		this->k_diffuse.x = 0.5;
		this->k_diffuse.y = 0.5;
		this->k_diffuse.z = 0.5;

		this->k_specular.x = 0.7;
		this->k_specular.y = 0.7;
		this->k_specular.z = 0.7;

		this->k_shineness = 10.0f;
	}
	else if (strcmp(material,"Pearl")==0)
	{
		this->k_ambient.x = 0.25f;
		this->k_ambient.y = 0.20725f;
		this->k_ambient.z = 0.20725f;


		this->k_diffuse.x = 1.0f;
		this->k_diffuse.y = 0.829;
		this->k_diffuse.z = 0.829;

		this->k_specular.x = 0.296648;
		this->k_specular.y = 0.296648;
		this->k_specular.z = 0.296648;

		this->k_shineness = 11.264f;
	}
	else if (strcmp(material,"Yellow")==0)
	{
		this->k_ambient.x = 0.0f;
		this->k_ambient.y = 0.0f;
		this->k_ambient.z = 0.0f;


		this->k_diffuse.x = 0.5;
		this->k_diffuse.y = 0.5;
		this->k_diffuse.z = 0.0f;

		this->k_specular.x = 0.6;
		this->k_specular.y = 0.6;
		this->k_specular.z = 0.5;

		this->k_shineness = 10.0f;
	}
	else if (strcmp(material,"Black")==0)
	{
		this->k_ambient.x = 0.0f;
		this->k_ambient.y = 0.0f;
		this->k_ambient.z = 0.0f;


		this->k_diffuse.x = 0.01;
		this->k_diffuse.y = 0.01;
		this->k_diffuse.z = 0.01;

		this->k_specular.x = 0.5;
		this->k_specular.y = 0.5;
		this->k_specular.z = 0.5;

		this->k_shineness = 32.0f;
	}
	else if (strcmp(material,"Green")==0)
	{
		this->k_ambient.x = 0.0f;
		this->k_ambient.y = 0.05f;
		this->k_ambient.z = 0.0f;


		this->k_diffuse.x = 0.4;
		this->k_diffuse.y = 0.5;
		this->k_diffuse.z = 0.4;

		this->k_specular.x = 0.04;
		this->k_specular.y = 0.7;
		this->k_specular.z = 0.04;

		this->k_shineness = 10.0f;
	}
	else if (strcmp(material,"Brass")==0)
	{
		this->k_ambient.x = 0.33f;
		this->k_ambient.y = 0.22f;
		this->k_ambient.z = 0.02f;


		this->k_diffuse.x = 0.78f;
		this->k_diffuse.y = 0.57f;
		this->k_diffuse.z = 0.11f;

		this->k_specular.x = 0.99f;
		this->k_specular.y = 0.39f;
		this->k_specular.z = 0.81f;

		this->k_shineness = 27.90f;
	}
	else if (strcmp(material,"Bronze")==0)
	{
		this->k_ambient.x = 0.21f;
		this->k_ambient.y = 0.12f;
		this->k_ambient.z = 0.05f;


		this->k_diffuse.x = 0.71f;
		this->k_diffuse.y = 0.43f;
		this->k_diffuse.z = 0.18f;

		this->k_specular.x = 0.39f;
		this->k_specular.y = 0.27f;
		this->k_specular.z = 0.17f;

		this->k_shineness = 25.6f;
	}
	else if (strcmp(material,"Chrome")==0)
	{
		this->k_ambient.x = 0.25f;
		this->k_ambient.y = 0.25f;
		this->k_ambient.z = 0.25f;


		this->k_diffuse.x = 0.4f;
		this->k_diffuse.y = 0.4f;
		this->k_diffuse.z = 0.4f;

		this->k_specular.x = 0.77f;
		this->k_specular.y = 0.77f;
		this->k_specular.z = 0.77f;

		this->k_shineness = 76.8f;
	}
	else if (strcmp(material,"Copper")==0)
	{
		this->k_ambient.x = 0.19f;
		this->k_ambient.y = 0.07f;
		this->k_ambient.z = 0.02f;


		this->k_diffuse.x = 0.70f;
		this->k_diffuse.y = 0.27f;
		this->k_diffuse.z = 0.08f;

		this->k_specular.x = 0.25f;
		this->k_specular.y = 0.14f;
		this->k_specular.z = 0.09f;

		this->k_shineness = 12.8f;
	}
	else if (strcmp(material,"Emerald")==0)
	{
		this->k_ambient.x = 0.02f;
		this->k_ambient.y = 0.17f;
		this->k_ambient.z = 0.02f;


		this->k_diffuse.x = 0.76f;
		this->k_diffuse.y = 0.61f;
		this->k_diffuse.z = 0.08f;

		this->k_specular.x = 0.63f;
		this->k_specular.y = 0.73f;
		this->k_specular.z = 0.63f;

		this->k_shineness = 76.8f;
	}
	else if (strcmp(material,"Jade")==0)
	{
		this->k_ambient.x = 0.14f;
		this->k_ambient.y = 0.22f;
		this->k_ambient.z = 0.16f;


		this->k_diffuse.x = 0.54f;
		this->k_diffuse.y = 0.89f;
		this->k_diffuse.z = 0.63f;

		this->k_specular.x = 0.32f;
		this->k_specular.y = 0.32f;
		this->k_specular.z = 0.32f;

		this->k_shineness = 12.8f;
	}
	else if (strcmp(material,"Obsidian")==0)
	{
		this->k_ambient.x = 0.05f;
		this->k_ambient.y = 0.05f;
		this->k_ambient.z = 0.07f;


		this->k_diffuse.x = 0.18f;
		this->k_diffuse.y = 0.17f;
		this->k_diffuse.z = 0.23f;

		this->k_specular.x = 0.33f;
		this->k_specular.y = 0.33f;
		this->k_specular.z = 0.35f;

		this->k_shineness = 38.4f;
	}
	else if (strcmp(material,"Ruby")==0)
	{
		this->k_ambient.x = 0.17f;
		this->k_ambient.y = 0.01f;
		this->k_ambient.z = 0.01f;


		this->k_diffuse.x = 0.61f;
		this->k_diffuse.y = 0.04f;
		this->k_diffuse.z = 0.04f;

		this->k_specular.x = 0.73f;
		this->k_specular.y = 0.63f;
		this->k_specular.z = 0.63f;

		this->k_shineness = 76.8f;
	}
	else if (strcmp(material,"Silver")==0)
	{
		this->k_ambient.x = 0.19f;
		this->k_ambient.y = 0.19f;
		this->k_ambient.z = 0.19f;


		this->k_diffuse.x = 0.51f;
		this->k_diffuse.y = 0.51f;
		this->k_diffuse.z = 0.51f;

		this->k_specular.x = 0.51f;
		this->k_specular.y = 0.51f;
		this->k_specular.z = 0.51f;

		this->k_shineness = 27.f;
	}
	else if (strcmp(material,"Turquoise")==0)
	{
		this->k_ambient.x = 0.1f;
		this->k_ambient.y = 0.19f;
		this->k_ambient.z = 0.17f;


		this->k_diffuse.x = 0.40f;
		this->k_diffuse.y = 0.74f;
		this->k_diffuse.z = 0.69f;

		this->k_specular.x = 0.29f;
		this->k_specular.y = 0.31f;
		this->k_specular.z = 0.31f;

		this->k_shineness = 12.8f;
	}
	else if (strcmp(material,"Plastic_Black")==0)
	{
		this->k_ambient.x = 0.0f;
		this->k_ambient.y = 0.0f;
		this->k_ambient.z = 0.0f;


		this->k_diffuse.x = 0.01f;
		this->k_diffuse.y = 0.01f;
		this->k_diffuse.z = 0.01f;

		this->k_specular.x = 0.50f;
		this->k_specular.y = 0.50f;
		this->k_specular.z = 0.50f;

		this->k_shineness = 32.0f;
	}
	else if (strcmp(material,"Plastic_Cyan")==0)
	{
		this->k_ambient.x = 0.0f;
		this->k_ambient.y = 0.1f;
		this->k_ambient.z = 0.06f;


		this->k_diffuse.x = 0.0f;
		this->k_diffuse.y = 0.51f;
		this->k_diffuse.z = 0.51f;

		this->k_specular.x = 0.50f;
		this->k_specular.y = 0.50f;
		this->k_specular.z = 0.50f;

		this->k_shineness = 32.0f;
	}
	else if (strcmp(material,"Plastic_Green")==0)
	{
		this->k_ambient.x = 0.0f;
		this->k_ambient.y = 0.0f;
		this->k_ambient.z = 0.0f;


		this->k_diffuse.x = 0.1f;
		this->k_diffuse.y = 0.35f;
		this->k_diffuse.z = 0.1f;

		this->k_specular.x = 0.45f;
		this->k_specular.y = 0.55f;
		this->k_specular.z = 0.45f;

		this->k_shineness = 32.0f;
	}
	else if (strcmp(material,"Plastic_Red")==0)
	{
		this->k_ambient.x = 0.0f;
		this->k_ambient.y = 0.0f;
		this->k_ambient.z = 0.0f;


		this->k_diffuse.x = 0.5f;
		this->k_diffuse.y = 0.0f;
		this->k_diffuse.z = 0.0f;

		this->k_specular.x = 0.7f;
		this->k_specular.y = 0.6f;
		this->k_specular.z = 0.6f;

		this->k_shineness = 32.0f;
	}
	else if (strcmp(material,"Plastic_White")==0)
	{
		this->k_ambient.x = 0.0f;
		this->k_ambient.y = 0.0f;
		this->k_ambient.z = 0.0f;


		this->k_diffuse.x = 0.55f;
		this->k_diffuse.y = 0.55f;
		this->k_diffuse.z = 0.55f;

		this->k_specular.x = 0.7f;
		this->k_specular.y = 0.7f;
		this->k_specular.z = 0.7f;

		this->k_shineness = 32.0f;
	}
	else if (strcmp(material,"Plastic_Yellow")==0)
	{
		this->k_ambient.x = 0.0f;
		this->k_ambient.y = 0.0f;
		this->k_ambient.z = 0.0f;


		this->k_diffuse.x = 0.5f;
		this->k_diffuse.y = 0.5f;
		this->k_diffuse.z = 0.0f;

		this->k_specular.x = 0.6f;
		this->k_specular.y = 0.6f;
		this->k_specular.z = 0.5f;

		this->k_shineness = 32.0f;
	}
	else if (strcmp(material,"Rubber_Black")==0)
	{
		this->k_ambient.x = 0.02f;
		this->k_ambient.y = 0.02f;
		this->k_ambient.z = 0.02f;


		this->k_diffuse.x = 0.01f;
		this->k_diffuse.y = 0.01f;
		this->k_diffuse.z = 0.01f;

		this->k_specular.x = 0.4f;
		this->k_specular.y = 0.4f;
		this->k_specular.z = 0.4f;

		this->k_shineness = 10.0f;
	}
	else if (strcmp(material,"Rubber_Cyan")==0)
	{
		this->k_ambient.x = 0.0f;
		this->k_ambient.y = 0.05f;
		this->k_ambient.z = 0.05f;


		this->k_diffuse.x = 0.4f;
		this->k_diffuse.y = 0.4f;
		this->k_diffuse.z = 0.5f;

		this->k_specular.x = 0.04f;
		this->k_specular.y = 0.7f;
		this->k_specular.z = 0.7f;

		this->k_shineness = 10.0f;
	}
	else if (strcmp(material,"Rubber_Green")==0)
	{
		this->k_ambient.x = 0.0f;
		this->k_ambient.y = 0.05f;
		this->k_ambient.z = 0.0f;


		this->k_diffuse.x = 0.4f;
		this->k_diffuse.y = 0.5f;
		this->k_diffuse.z = 0.4f;

		this->k_specular.x = 0.04f;
		this->k_specular.y = 0.7f;
		this->k_specular.z = 0.04f;

		this->k_shineness = 10.0f;
	}
	else if (strcmp(material,"Rubber_Red")==0)
	{
		this->k_ambient.x = 0.05f;
		this->k_ambient.y = 0.0f;
		this->k_ambient.z = 0.0f;


		this->k_diffuse.x = 0.5f;
		this->k_diffuse.y = 0.4f;
		this->k_diffuse.z = 0.4f;

		this->k_specular.x = 0.7f;
		this->k_specular.y = 0.04f;
		this->k_specular.z = 0.04f;

		this->k_shineness = 10.0f;
	}
	else if (strcmp(material,"Rubber_White")==0)
	{
		this->k_ambient.x = 0.05f;
		this->k_ambient.y = 0.05f;
		this->k_ambient.z = 0.05f;


		this->k_diffuse.x = 0.5f;
		this->k_diffuse.y = 0.5f;
		this->k_diffuse.z = 0.5f;

		this->k_specular.x = 0.7f;
		this->k_specular.y = 0.7f;
		this->k_specular.z = 0.7f;

		this->k_shineness = 10.0f;

	}
	else if (strcmp(material,"Rubber_Yellow")==0)
	{
		this->k_ambient.x = 0.05f;
		this->k_ambient.y = 0.05f;
		this->k_ambient.z = 0.0f;


		this->k_diffuse.x = 0.5f;
		this->k_diffuse.y = 0.5f;
		this->k_diffuse.z = 0.4f;

		this->k_specular.x = 0.7f;
		this->k_specular.y = 0.7f;
		this->k_specular.z = 0.04f;

		this->k_shineness = 10.0f;
	}
	else
	{
		printf("wrong color input\n");
	}
}
