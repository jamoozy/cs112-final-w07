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

typedef int Vector3i[9];

void moveCube(double x, double y, double z);
void drawCube();
void drawCube1();
void drawRevolver();
void drawRoom();

int IsVertexInBox(Vector3f vertex, GLfloat cube[6][4][3], 
				   Vector3i& faceHit, bool mustBeInside);
int Collide(GLfloat cube1[6][4][3], GLfloat cube2[6][4][3], bool mustBeInTheBox,
			Vector3i& faceHit);
bool CheckAllCollisions(GLfloat TMPcubeVertexes[6][4][3], 
						GLfloat TMPcubeVertexes1[6][4][3], 
						GLfloat TMPrevolverVertexes[6][4][3], 
						GLfloat TMProomVertexes[6][4][3]);
void moveSpinnerRevolver();
void InvertMoveVector(Vector3f& vector, int hitCount, Vector3i faceHit);

#ifdef __cplusplus
}
#endif


#endif
