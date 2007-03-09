#include <signal.h>
#include <sys/types.h>
#include "inputModule.h"
#include "PLY.h"

/* This File contains the KeyBoard and mouse handling routines */


static int motionMode;
static int startX;
static int startY;

static GLfloat angle1 = 0;    /* in degrees */
static GLfloat angle2 = 0;   /* in degrees */

GLfloat current_pos[] = {0.0, 0.0, 0.0};
GLfloat move_speed = 0.25;

int wire = 0;
int flat = 0;
int light = 1;

extern PLYObject* ply;

void readKeyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'w':
		case 'W':
			current_pos[2] -= move_speed;
			break;
		case 'a':
		case 'A':
			current_pos[0] -= move_speed;
			break;
		case 's':
		case 'S':
			current_pos[2] += move_speed;
			break;
		case 'd':
		case 'D':
			current_pos[0] += move_speed;
			break;
		case  0x1B:
		case  'q':
		case  'Q':
			exit(0);
			break; 
		case 'r':
		case 'R':
			// reset initial view parameters
			angle1 = 20;
			angle2 = 30;
			current_pos[0] = 0.0;
			current_pos[1] = 0.0;
			current_pos[2] = 0.0;
			break;
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
	switch(motionMode){
		case 0:
			return;
			break;

		case 1: // Calculate the rotations
			angle1 = angle1 + (x - startX);
			angle2 = angle2 + (y - startY);
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

	glutPostRedisplay();
}


void setUserView()
{
	glLoadIdentity();

	glTranslatef(-current_pos[0], current_pos[1], -current_pos[2]);
	glRotatef(angle2, 1.0, 0.0, 0.0);
	glRotatef(angle1, 0.0, 1.0, 0.0);
}
