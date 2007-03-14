#ifndef  CUBE_H
#define  CUBE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#ifdef __APPLE__
#include <glut/glut.h>
#else
#include <GL/glut.h>
#endif

#include "geometry.h"

#ifdef __cplusplus
extern "C" {
#endif

void drawCube();
void drawRevolver();
void drawRoom();

bool IsVertexInBox(Vector3f vertex, GLfloat cube[6][4][3]);
bool Collide(GLfloat cube1[6][4][3], GLfloat cube2[6][4][3], bool mustBeInTheBox);
void CheckAllCollisions();
void moveSpinnerRevolver();
void InvertMoveVector(Vector3f* vector);

#ifdef __cplusplus
}
#endif


#endif
