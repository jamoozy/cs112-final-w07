// Andrew Correa
// 60926645
// acorrea@uci.edu



#ifdef WIN32
#include <windows.h>
#endif
#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif
#include "viewModule.h"
#include "inputModule.h"
#include "cube.h"
#include "bouncer.h"
#include "PLY.h"
#include "geometry.h"

int window;
int updateFlag;

bool running_mode = kay;

Bouncer *bouncer;

perspectiveData pD;

Vector4f initial_light_pos = {-10.0, 10.0, 10.0, 1.0};
Vector4f ambient_light = {0.3, 0.3, 0.3, 1.0};
Vector4f light_color = {0.6, 0.6, 0.6, 1.0};
Vector4f black_color = {0.0, 0.0, 0.0, 1.0};

Vector3f light_pos, viewer_pos;

extern GLfloat current_pos[3];

void cleanup(int sig)
{
	// insert cleanup code here (i.e. deleting structures or so)
	//fprintf(stderr,"Cleaning up\n");
	if (bouncer)
		delete(bouncer);
	exit(0);
}


//##########################################
// OpenGL Display function

void display(void)
{
	int i, j;
	float M[16];
	Matrix4f m;

	glutSetWindow(window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	setUserView();

	glGetFloatv(GL_MODELVIEW_MATRIX, M);
	for (i = 0; i < 3; i++) {
		m[i][3] = 0.0;
		m[3][i] = 0.0;
		for (j = 0; j < 3; j++) {
			m[i][j] = M[i*4+j];
		}
	}
	m[3][3] = 1.0;
	multVector(light_pos, m, initial_light_pos);
	multVector(viewer_pos, m, current_pos);

	//drawCube();
	

	if (running_mode == andrew)
	{
		// Draw the ground floor.
		glColor3f(0,1,0);
		glBegin(GL_QUADS);
			glVertex3f(pD.farPlane, Bouncer::FLOOR, pD.farPlane);
			glVertex3f(-pD.farPlane, Bouncer::FLOOR, pD.farPlane);
			glVertex3f(-pD.farPlane, Bouncer::FLOOR, -pD.farPlane);
			glVertex3f(pD.farPlane, Bouncer::FLOOR, -pD.farPlane);
		glEnd();
		bouncer->draw();
	}
	else
		drawCube();

	glutSwapBuffers();
}


//##########################################
// Init display settings

void initDisplay()
{
	// Perspective projection parameters
	pD.fieldOfView = 45.0;
	pD.aspect      = (float)IMAGE_WIDTH/IMAGE_HEIGHT;
	pD.nearPlane   = 0.1;
	pD.farPlane    = 500.0;

	// setup context
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(pD.fieldOfView, pD.aspect, pD.nearPlane, pD.farPlane);

	// set basic matrix mode
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClearIndex(0);
	glClearDepth(1);

	// setup lights
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black_color);
	glLightfv(GL_LIGHT0, GL_POSITION, initial_light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_color);
}

//##########################################
// Main function

int main(int argc, char **argv)
{
	if (argc > 1) printf("2nd param: %s\n", argv[1]);

	//signal(SIGHUP, cleanup);
	// Set up which demo we're going to run:
	if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'a')
	{
		printf("Running mode is ANDREW\n");
		running_mode = andrew;
		current_pos[0] = 0;
		current_pos[1] = 0;
		current_pos[2] = -20;
	}
	else
	{
		printf("Running mode is KAY\n");
		running_mode = kay;
		current_pos[0] = 0;
		current_pos[1] = 0;
		current_pos[2] = 0;
	}

	glutInit(&argc, argv);

	if (running_mode == andrew)
		bouncer = new Bouncer();
	else
		bouncer = NULL;

	srand(time(NULL));

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(IMAGE_WIDTH,IMAGE_HEIGHT);

	window = glutCreateWindow("Final - Colision Detection");

	glutDisplayFunc(display);
	glutKeyboardFunc(readKeyboard);
	glutMouseFunc(mouseButtHandler);
	glutMotionFunc(mouseMoveHandler);
	glutPassiveMotionFunc(mouseMoveHandler);
	glutIdleFunc(display);

	initDisplay();

	glutMainLoop();

	return 0;             /* ANSI C requires main to return int. */
}
