#include "argparse.hpp"
#include <stdio.h>
#include <stdlib.h>
#include "GL/freeglut.h"

#include "raytrace.h"
#include "functions.h"//includees "quat.h" "vector.h" "rotateVec.h"

#include "camera.h"

#include <vector>
//hyperparameters by argparser//
int WINDOWHEIGHT;
int WINDOWWIDTH;
int depth;
///////////////////////////////
using namespace std;

void initGL();
void EventHandlingLoop();
void Rendering();

Camera camera;
vector<object*> objects;

int main(int argc, char** argv)
{
	argparse::ArgumentParser program("testprogram_name");

	program.add_argument("-wh","--window_height").help("set window_height").nargs(1).default_value(50).action([](const string& v){return stoi(v);});
	program.add_argument("-ww","--window-width").help("set window_width").nargs(1).default_value(50).action([](const string& v){return stoi(v);});
	program.add_argument("-d", "--depth").help("set reflection depth").nargs(1).default_value(1).action([](const string&v ){return stoi(v);});

	try
	{
		program.parse_args(argc,argv);
	}
	catch(const runtime_error& err)
	{
		cout << "argparse failed" << endl;
		cout << err.what() << endl;
		cout << program;
		exit(0);
	}

	WINDOWHEIGHT=program.get<int>("-wh");
	WINDOWWIDTH=program.get<int>("-ww");
	depth=program.get<int>("-d");

	glutInit(&argc, argv);
	initGL();
	VECTOR3D sphere1center(0.0f, -10.0f, 15.0f);
	VECTOR3D sphere2center(20.0f, 20.0f, 10.0f);
	VECTOR3D sphere3center(-20.0f, 10.0f, 7.0f);


	sphere sphere1(sphere1center, 15.0, "Pearl");
	//sphere sphere1(sphere1center, 40.0, "Pearl");
	sphere sphere2(sphere2center, 10.0, "Cyan");
	sphere sphere3(sphere3center, 7.0, "Yellow");

	VECTOR3D floorNormal(0, 0, 1);
	VECTOR3D wall1Normal(0, 1, 0);
	VECTOR3D wall2Normal(1, 0, 0);
	VECTOR3D wall3Normal(0, -1, 0);
	VECTOR3D wall4Normal(-1, 0, 0);
	VECTOR3D ceilingNormal(0, 0, -1);


	plane floor(0, floorNormal, 'z', "White");
	plane wall1(-100, wall1Normal, 'y', "White");
	plane wall2(-100, wall2Normal, 'x', "White");
	plane wall3(100, wall3Normal, 'y', "White");
	plane wall4(100, wall4Normal, 'x', "White");
	plane ceiling(2000, ceilingNormal, 'z', "White");

	objects.push_back(&sphere1);

	objects.push_back(&sphere2);
	objects.push_back(&sphere3);
	objects.push_back(&floor);
	objects.push_back(&wall1);
	objects.push_back(&wall2);
	objects.push_back(&wall3);
	objects.push_back(&wall4);
	//objects.push_back(&ceiling);

	EventHandlingLoop();
	return 0;
}



void initGL()
{
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(400, 100);
	glutInitWindowSize(WINDOWWIDTH, WINDOWHEIGHT);
	glutCreateWindow("OpenGL Lecture");
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glDisable(GL_CULL_FACE);
}

void Rendering()
{
	static int i = 0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluPerspective(100, 1, 0.01, 1);
	gluLookAt(camera.position.x, camera.position.y, camera.position.z, \
		camera.direction.x, camera.direction.y, camera.direction.z, \
		camera.top.x, camera.top.y, camera.top.z);

	GLdouble modelView[16];
	GLdouble projection[16];
	GLint viewPort[4];
	//VECTOR3D light1(0,0,50);
	VECTOR3D light1(30, -40, 40);
	//VECTOR3D light1(60, 70, 0);
	VECTOR3D light2(-30, -40, 40);
	VECTOR3D light3(0, 40, 40);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewPort);
	glBegin(GL_POINTS);
	for (int i = 0; i < glutGet(GLUT_WINDOW_WIDTH); i++)
	{
		for (int j = 0; j < glutGet(GLUT_WINDOW_HEIGHT); j++)
		{
			/*
			double nearX, nearY, nearZ;

			gluUnProject(i+0.5, j + 0.5, 0.001, modelView, projection, viewPort, &nearX, &nearY, &nearZ);
			VECTOR3D nearVec((float)nearX, (float)nearY, (float)nearZ);
			Ray ray(camera.position, nearVec - camera.position);

			VECTOR3D color1 = raytrace(ray, depth, &objects, light1);//0 means depth
			//VECTOR3D color2 = raytrace(ray, depth, &objects, light2);//0 means depth
			//VECTOR3D color3 = raytrace(ray, depth, &objects, light3);//0 means depth

			//VECTOR3D finalColor = (color1 + color2 + color3) / 3.0;
			//glColor3f(finalColor.x, finalColor.y, finalColor.z);
			glColor3f(color1.x,color1.y,color1.z);

			glVertex3f(nearVec.x,nearVec.y,nearVec.z);

				*/
				///////////////////////////////anti alising
			double nearX, nearY, nearZ;
			VECTOR3D nearVec;
			VECTOR3D color1, color2, color3, color4, color5, color6, color7, color8, color9;
			gluUnProject(i, j, 0.001, modelView, projection, viewPort, &nearX, &nearY, &nearZ);
			nearVec.x = (float)nearX;
			nearVec.y = (float)nearY;
			nearVec.z = (float)nearZ;
			Ray ray = Ray(camera.position, nearVec - camera.position);
			color1 = raytrace(ray, depth, &objects, light1);//0 means depth
			
			
			gluUnProject(i + 0.5, j, 0.001, modelView, projection, viewPort, &nearX, &nearY, &nearZ);
			nearVec.x = (float)nearX;
			nearVec.y = (float)nearY;
			nearVec.z = (float)nearZ;
			ray= Ray(camera.position, nearVec - camera.position);

			color2 = raytrace(ray, depth, &objects, light1);//0 means depth


			gluUnProject(i + 1, j, 0.001, modelView, projection, viewPort, &nearX, &nearY, &nearZ);
			nearVec.x = (float)nearX;
			nearVec.y = (float)nearY;
			nearVec.z = (float)nearZ;
			ray = Ray(camera.position, nearVec - camera.position);

			color3 = raytrace(ray, depth, &objects, light1);//0 means depth


			gluUnProject(i + 1, j + 0.5, 0.001, modelView, projection, viewPort, &nearX, &nearY, &nearZ);
			nearVec.x = (float)nearX;
			nearVec.y = (float)nearY;
			nearVec.z = (float)nearZ;
			ray = Ray(camera.position, nearVec - camera.position);

			color4 = raytrace(ray, depth, &objects, light1);//0 means depth


			gluUnProject(i + 1, j + 1, 0.001, modelView, projection, viewPort, &nearX, &nearY, &nearZ);
			nearVec.x = (float)nearX;
			nearVec.y = (float)nearY;
			nearVec.z = (float)nearZ;
			ray = Ray(camera.position, nearVec - camera.position);

			color5 = raytrace(ray, depth, &objects, light1);//0 means depth


			gluUnProject(i + 0.5, j + 1, 0.001, modelView, projection, viewPort, &nearX, &nearY, &nearZ);
			nearVec.x = (float)nearX;
			nearVec.y = (float)nearY;
			nearVec.z = (float)nearZ;
			ray = Ray(camera.position, nearVec - camera.position);

			color6 = raytrace(ray, depth, &objects, light1);//0 means depth


			gluUnProject(i, j + 1, 0.001, modelView, projection, viewPort, &nearX, &nearY, &nearZ);
			nearVec.x = (float)nearX;
			nearVec.y = (float)nearY;
			nearVec.z = (float)nearZ;
			ray = Ray(camera.position, nearVec - camera.position);

			color7 = raytrace(ray, depth, &objects, light1);//0 means depth


			gluUnProject(i, j + 0.5, 0.001, modelView, projection, viewPort, &nearX, &nearY, &nearZ);
			nearVec.x = (float)nearX;
			nearVec.y = (float)nearY;
			nearVec.z = (float)nearZ;
			ray = Ray(camera.position, nearVec - camera.position);

			color8 = raytrace(ray, depth, &objects, light1);//0 means depth


			gluUnProject(i + 0.5, j + 0.5, 0.001, modelView, projection, viewPort, &nearX, &nearY, &nearZ);
			nearVec.x = (float)nearX;
			nearVec.y = (float)nearY;
			nearVec.z = (float)nearZ;
			ray = Ray(camera.position, nearVec - camera.position);

			color9 = raytrace(ray, depth, &objects, light1);//0 means depth

			VECTOR3D finalColor1 = (color1 + color2 + color3 + color4 + color5 + color6 + color7 + color8 + color9) / 9.0;

			/////////////
			gluUnProject(i, j, 0.001, modelView, projection, viewPort, &nearX, &nearY, &nearZ);
			nearVec.x = (float)nearX;
			nearVec.y = (float)nearY;
			nearVec.z = (float)nearZ;
			ray = Ray(camera.position, nearVec - camera.position);

			color1 = raytrace(ray, depth, &objects, light2);//0 means depth
			gluUnProject(i + 0.5, j, 0.001, modelView, projection, viewPort, &nearX, &nearY, &nearZ);
			nearVec.x = (float)nearX;
			nearVec.y = (float)nearY;
			nearVec.z = (float)nearZ;
			ray = Ray(camera.position, nearVec - camera.position);

			color2 = raytrace(ray, depth, &objects, light2);//0 means depth


			gluUnProject(i + 1, j, 0.001, modelView, projection, viewPort, &nearX, &nearY, &nearZ);
			nearVec.x = (float)nearX;
			nearVec.y = (float)nearY;
			nearVec.z = (float)nearZ;
			ray = Ray(camera.position, nearVec - camera.position);

			color3 = raytrace(ray, depth, &objects, light2);//0 means depth


			gluUnProject(i + 1, j + 0.5, 0.001, modelView, projection, viewPort, &nearX, &nearY, &nearZ);
			nearVec.x = (float)nearX;
			nearVec.y = (float)nearY;
			nearVec.z = (float)nearZ;
			ray = Ray(camera.position, nearVec - camera.position);

			color4 = raytrace(ray, depth, &objects, light2);//0 means depth


			gluUnProject(i + 1, j + 1, 0.001, modelView, projection, viewPort, &nearX, &nearY, &nearZ);
			nearVec.x = (float)nearX;
			nearVec.y = (float)nearY;
			nearVec.z = (float)nearZ;
			ray = Ray(camera.position, nearVec - camera.position);

			color5 = raytrace(ray, depth, &objects, light2);//0 means depth


			gluUnProject(i + 0.5, j + 1, 0.001, modelView, projection, viewPort, &nearX, &nearY, &nearZ);
			nearVec.x = (float)nearX;
			nearVec.y = (float)nearY;
			nearVec.z = (float)nearZ;
			ray = Ray(camera.position, nearVec - camera.position);

			color6 = raytrace(ray, depth, &objects, light2);//0 means depth


			gluUnProject(i, j + 1, 0.001, modelView, projection, viewPort, &nearX, &nearY, &nearZ);
			nearVec.x = (float)nearX;
			nearVec.y = (float)nearY;
			nearVec.z = (float)nearZ;
			ray = Ray(camera.position, nearVec - camera.position);

			color7 = raytrace(ray, depth, &objects, light2);//0 means depth


			gluUnProject(i, j + 0.5, 0.001, modelView, projection, viewPort, &nearX, &nearY, &nearZ);
			nearVec.x = (float)nearX;
			nearVec.y = (float)nearY;
			nearVec.z = (float)nearZ;
			ray = Ray(camera.position, nearVec - camera.position);

			color8 = raytrace(ray, depth, &objects, light2);//0 means depth


			gluUnProject(i + 0.5, j + 0.5, 0.001, modelView, projection, viewPort, &nearX, &nearY, &nearZ);
			nearVec.x = (float)nearX;
			nearVec.y = (float)nearY;
			nearVec.z = (float)nearZ;
			ray = Ray(camera.position, nearVec - camera.position);

			color9 = raytrace(ray, depth, &objects, light2);//0 means depth

			VECTOR3D finalColor2 = (color1 + color2 + color3 + color4 + color5 + color6 + color7 + color8 + color9) / 9.0;

			///////////
			gluUnProject(i, j, 0.001, modelView, projection, viewPort, &nearX, &nearY, &nearZ);
			nearVec.x = (float)nearX;
			nearVec.y = (float)nearY;
			nearVec.z = (float)nearZ;
			ray = Ray(camera.position, nearVec - camera.position);

			color1 = raytrace(ray, depth, &objects, light3);//0 means depth
			gluUnProject(i + 0.5, j, 0.001, modelView, projection, viewPort, &nearX, &nearY, &nearZ);
			nearVec.x = (float)nearX;
			nearVec.y = (float)nearY;
			nearVec.z = (float)nearZ;
			ray = Ray(camera.position, nearVec - camera.position);

			color2 = raytrace(ray, depth, &objects, light3);//0 means depth


			gluUnProject(i + 1, j, 0.001, modelView, projection, viewPort, &nearX, &nearY, &nearZ);
			nearVec.x = (float)nearX;
			nearVec.y = (float)nearY;
			nearVec.z = (float)nearZ;
			ray = Ray(camera.position, nearVec - camera.position);

			color3 = raytrace(ray, depth, &objects, light3);//0 means depth


			gluUnProject(i + 1, j + 0.5, 0.001, modelView, projection, viewPort, &nearX, &nearY, &nearZ);
			nearVec.x = (float)nearX;
			nearVec.y = (float)nearY;
			nearVec.z = (float)nearZ;
			ray = Ray(camera.position, nearVec - camera.position);

			color4 = raytrace(ray, depth, &objects, light3);//0 means depth


			gluUnProject(i + 1, j + 1, 0.001, modelView, projection, viewPort, &nearX, &nearY, &nearZ);
			nearVec.x = (float)nearX;
			nearVec.y = (float)nearY;
			nearVec.z = (float)nearZ;
			ray = Ray(camera.position, nearVec - camera.position);

			color5 = raytrace(ray, depth, &objects, light3);//0 means depth


			gluUnProject(i + 0.5, j + 1, 0.001, modelView, projection, viewPort, &nearX, &nearY, &nearZ);
			nearVec.x = (float)nearX;
			nearVec.y = (float)nearY;
			nearVec.z = (float)nearZ;
			ray = Ray(camera.position, nearVec - camera.position);

			color6 = raytrace(ray, depth, &objects, light3);//0 means depth


			gluUnProject(i, j + 1, 0.001, modelView, projection, viewPort, &nearX, &nearY, &nearZ);
			nearVec.x = (float)nearX;
			nearVec.y = (float)nearY;
			nearVec.z = (float)nearZ;
			ray = Ray(camera.position, nearVec - camera.position);

			color7 = raytrace(ray, depth, &objects, light3);//0 means depth


			gluUnProject(i, j + 0.5, 0.001, modelView, projection, viewPort, &nearX, &nearY, &nearZ);
			nearVec.x = (float)nearX;
			nearVec.y = (float)nearY;
			nearVec.z = (float)nearZ;
			ray = Ray(camera.position, nearVec - camera.position);

			color8 = raytrace(ray, depth, &objects, light3);//0 means depth


			gluUnProject(i + 0.5, j + 0.5, 0.001, modelView, projection, viewPort, &nearX, &nearY, &nearZ);
			nearVec.x = (float)nearX;
			nearVec.y = (float)nearY;
			nearVec.z = (float)nearZ;
			ray = Ray(camera.position, nearVec - camera.position);

			color9 = raytrace(ray, depth, &objects, light3);//0 means depth


			VECTOR3D finalColor3 = (color1 + color2 + color3 + color4 + color5 + color6 + color7 + color8 + color9) / 9.0;

			VECTOR3D finalColor = (finalColor1 + finalColor2 + finalColor3) / 3.0;
			glColor3f(finalColor.x, finalColor.y, finalColor.z);
			glVertex3f(nearVec.x, nearVec.y, nearVec.z);
			////////////////////////////////////////////////////////////
		}
		printf("row %d render complete\n", i);

	}
	glEnd();
	glutSwapBuffers();
	printf("rendered %d\n", i++);


}

void EventHandlingLoop()
{
	glutDisplayFunc(Rendering);
	glutMainLoop();
}
