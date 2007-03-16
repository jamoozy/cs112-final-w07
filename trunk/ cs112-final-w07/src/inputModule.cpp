//#############################################
//  Khoa Dang 17638455
//  CS112 - Winter 2007
//  Final Project
//#############################################

#ifdef WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <math.h>
#include "inputModule.h"
#include "bouncer.h"
#include "debug.h"
#include "cube.h"


static int motionMode;
static int startX;
static int startY;

static GLfloat angle1 = 0;    /* in degrees */
static GLfloat angle2 = 0;   /* in degrees */

GLfloat current_pos[] = {0.0, 0.0, 0.0};
GLfloat rcurrent_pos[] = {5.0, 5.0, 5.0};
GLfloat move_speed = 0.25;
GLfloat rot_speed = 0.25;

int wire = 0;
int flat = 0;
int light = 1;

extern Bouncer *bouncer;
extern bool running_mode;

void readKeyboard(unsigned char key, int x, int y)
{
	if (key == 'm' || key == 'M')
	{
		running_mode = !running_mode;
		if (running_mode == andrew)
		{
			current_pos[0] = 0;
			current_pos[1] = 0;
			current_pos[2] = -34;
		}
		else
		{
			current_pos[0] = 0;
			current_pos[1] = 0;
			current_pos[2] = -10;
		}
		return;
	}

	if (running_mode == kay)
	{
		float a1 = angle1 * M_PI / 180.0f;
		switch(key)
		{
			case 'w':
			case 'W':
				current_pos[0] -= move_speed * sin(a1);
				current_pos[2] += move_speed * cos(a1);
				break;
			case 'a':
			case 'A':
				current_pos[0] += move_speed * cos(a1);
				current_pos[2] += move_speed * sin(a1);
				break;
			case 's':
			case 'S':
				current_pos[0] += move_speed * sin(a1);
				current_pos[2] -= move_speed * cos(a1);
				break;
			case 'd':
			case 'D':
				current_pos[0] -= move_speed * cos(a1);
				current_pos[2] -= move_speed * sin(a1);
				break;
			case  0x1B:
			case  'q':
			case  'Q':
				exit(0);
				break; 
			case 'x':
				moveCube(0.1,0,0);
				break;
			case 'X':
				moveCube(-0.1,0,0);
				break;
			case 'y':
				moveCube(0,0.1,0);
				break;
			case 'Y':
				moveCube(0,-0.1,0);
				break;
			case 'z':
				moveCube(0,0,0.1);
				break;
			case 'Z':
				moveCube(0,0,-0.1);
				break;
			case 'r':
			case 'R':
				// reset initial view parameters
				if (debugon) printf("pos:[%2.1f,%2.1f,%2.1f]\n", current_pos[0], current_pos[1], current_pos[2]);
				angle1 = 0;
				angle2 = 0;
				current_pos[0] = 0.0;
				current_pos[1] = 0.0;
				current_pos[2] = -20.0;
				trace(__FILE__,__LINE__,"Resetting...\n",0);
				break;
		}
	}
	else
	{
		switch (key)
		{
			case 's':
			case 'S':
				debug("Starting to fall...\n");
				bouncer->start();
				break;
			case 'r':
			case 'R':
				debug("Resetting...\n");
				bouncer->reset();
				break;
			case  0x1B:
			case  'q':
			case  'Q':
				exit(0);
				break; 
		}
	}
	glutPostRedisplay();
}


void readSpecialKeys(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP: 

			break;
		case GLUT_KEY_DOWN: 

			break;
		case GLUT_KEY_RIGHT: 

			break;
		case GLUT_KEY_LEFT:  

			break;
	}
	glutPostRedisplay();
}


void mouseButtHandler(int button, int state, int x, int y)
{
	motionMode = 0;

	switch(button)
	{
		case GLUT_LEFT_BUTTON:  
			if(state == GLUT_DOWN) {
				motionMode = 1;		// Rotate object
				startX = x;
				startY = y;
			}
			break;
		case GLUT_MIDDLE_BUTTON:  
			if(state == GLUT_DOWN) {
				motionMode = 2;		// Translate object
				startX = x;
				startY = y;
			}
			break;
		case GLUT_RIGHT_BUTTON: 
			if(state == GLUT_DOWN) { 
				motionMode = 3;		// Zoom
				startX = x;
				startY = y;
			}
			break;
	}
	glutPostRedisplay();
}


void mouseMoveHandler(int x, int y)
{

	// No mouse button is pressed... return 
	if (running_mode == kay)
	{
		switch(motionMode)
		{
			case 0:
				return;
				break;

			case 1: // Calculate the rotations
				angle1 += rot_speed * (x - startX);
				angle2 += rot_speed * (y - startY);
				startX = x;
				startY = y;
				break;

			case 2:
				current_pos[0] = current_pos[0] - (x - startX)/100.0;
				current_pos[1] = current_pos[1] - (y - startY)/100.0;
				startX = x;
				startY = y;
				break;

			case 3:
				current_pos[2] = current_pos[2] - (y - startY)/10.0;
				startX = x;
				startY = y;
				break;
		}
	}
	else
	{
		switch(motionMode)
		{
			case 0:
				return;
				break;
			case 1:
				if (!bouncer->running())
					bouncer->rotate(y-startY, x-startX);
			case 2:
			case 3:
				startX = x;
				startY = y;
				break;
		}
	}
	glutPostRedisplay();
}


void setUserView()
{
	glLoadIdentity();

	glTranslatef(current_pos[0], current_pos[1], current_pos[2]);
	glRotatef(angle2, 1.0, 0.0, 0.0);
	glRotatef(angle1, 0.0, 1.0, 0.0);
}
