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


#ifdef __cplusplus
extern "C" {
#endif

void drawCube();

#ifdef __cplusplus
}
#endif


#endif
