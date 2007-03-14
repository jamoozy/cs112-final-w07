

// Andrew Correa
// 60926645
// acorrea@uci.edu

////////////////////////////////////////////////////////////////////////////////
//        Declares some useful debug functions and a debug constant to        //
//                               toggle debug mode                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef DEBUG_H
#define DEBUG_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include "geometry.h"

#define debugon true
#define traceon false
#define debuglight true

// Print the string and specify whether to indent, un-indent, or neither.
void debug(char*);

// Traces out a message with the filename and line number.
void trace(char*, int, char*, int);

// Print the number in a special format.
//void debug(int);

// Print the matrix.
void printMatrix(GLdouble*);
void printMatrix(Matrix4d*);

// Print the vector.
void printVector(Vector3d);

// Print the multiplication.
void printMult(Matrix4d*,Vector4d*,Vector4d*);
void printMult(Matrix4d*,Matrix4d*,Matrix4d*);

#endif
