#ifndef INPUTMODULE_H
#define INPUTMODULE_H

#include <stdlib.h>
#ifdef __APPLE__
#include <glut/glut.h>
#else
#include <GL/glut.h>
#endif


extern GLfloat current_pos[];

#ifdef __cplusplus
extern "C" {
#endif
  
//static GLfloat rangle = 20;    /* in degrees */
//static GLfloat rangle2 = 30;   /* in degrees */


#define andrew true
#define kay false


void readKeyboard(unsigned char key, int x, int y);
void readSpecialKeys(int key, int x, int y);
void mouseButtHandler(int button, int state, int x, int y);
void mouseMoveHandler(int x, int y);
void setUserView();

#ifdef __cplusplus
}
#endif


#endif









