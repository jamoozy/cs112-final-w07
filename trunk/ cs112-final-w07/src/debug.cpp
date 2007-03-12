// Andrew Correa
// 60926645
// acorrea@uci.edu

////////////////////////////////////////////////////////////////////////////////
//      Defines some useful debugging functions that I use throughout.        //
////////////////////////////////////////////////////////////////////////////////

#ifdef __APPLE__

#else
#include <GL/gl.h>
#endif
#include <stdio.h>
#include "debug.h"
#include "geometry.h"

// For indentation of the traceing functions.
#define TABSIZE 3
// Keeps track of how far we are indented--helps keep a consistent feel.
int totalIndent = 0;

// Prints the passed string to the screen.  'indent' is positive for entering
// trace statements (ones at the top of the function, or as you enter the
// function), negative for leaving trace statements (ones at the bottom of
// the function, or as you're leaving it), and 0 when you just want to keep the
// indentation consistent.  This is usually used for "normal" prints.
void debug(char *str)
{
	if (debugon)
	{
		// This is the string that is responsible for indenting.
		char *indentstring = new char[totalIndent*TABSIZE+1];
		for (int i = 0; i < totalIndent*TABSIZE; i++)
			indentstring[i] = ' ';
		indentstring[totalIndent*TABSIZE] = '\0';

		printf(" %s%s", indentstring, str);

		// Clean up!
		delete[] indentstring;
	}
}

void trace(char *file, int line, char *str, int indent)
{
	if (traceon)
	{
		// If we're leaving a function, first un-indent, then print.
		if (indent < 0)
			totalIndent--;

		// This is the string that is responsible for indenting.
		char *indentstring = new char[totalIndent*TABSIZE+1];
		for (int i = 0; i < totalIndent*TABSIZE; i++)
			indentstring[i] = ' ';
		indentstring[totalIndent*TABSIZE] = '\0';

		char tmp[8];
		for (int i = 0; i < 8; i++)
		{
			tmp[i] = file[i+4];
			if (file[i+4] == '\0')
				break;
		}
		printf("%8.8s,%5d: %s%s", tmp, line, indentstring, str);

		// If we're entering a function, first print, then indent.
		if (indent > 0)
			totalIndent++;

		// Clean up!
		delete[] indentstring;
	}
}

// This is meant for line numbers, but is also used for other numbers.  It
// simply prints a colon after the number, and makes the number conform
// to a standart position.
//void debug(int i)
//{
//	if (debugon)
//	{
//		printf("% 5d: ", i);
//	}
//}

// Prints the matrix in column major order.
void printMatrix(GLdouble *m)
{
	if (debugon)
	{
		printf("[ % 2.1f % 2.1f % 2.1f % 2.1f ]\n", m[0], m[4], m[8], m[12]);
		printf("[ % 2.1f % 2.1f % 2.1f % 2.1f ]\n", m[1], m[5], m[9], m[13]);
		printf("[ % 2.1f % 2.1f % 2.1f % 2.1f ]\n", m[2], m[6], m[10], m[14]);
		printf("[ % 2.1f % 2.1f % 2.1f % 2.1f ]\n", m[3], m[7], m[11], m[15]);
	}
}

// Prints the matrix in column major order.
void printMatrix(Matrix4d *m)
{
	if (debugon)
	{
		printf("[ % 2.1f % 2.1f % 2.1f % 2.1f ]\n", (*m)[0][0], (*m)[0][4], (*m)[0][8], (*m)[0][12]);
		printf("[ % 2.1f % 2.1f % 2.1f % 2.1f ]\n", (*m)[0][1], (*m)[0][5], (*m)[0][9], (*m)[0][13]);
		printf("[ % 2.1f % 2.1f % 2.1f % 2.1f ]\n", (*m)[0][2], (*m)[0][6], (*m)[0][10], (*m)[0][14]);
		printf("[ % 2.1f % 2.1f % 2.1f % 2.1f ]\n", (*m)[0][3], (*m)[0][7], (*m)[0][11], (*m)[0][15]);
	}
}

void printVector(Vector3f v)
{
	if (debugon)
	{
		printf("[ % 2.1f %2.1f %2.1f ]\n", v[0], v[1], v[2]);
	}
}

void printMult(Matrix4d *m, Vector4d *u, Vector4d *v)
{
	if (debugon)
	{
		printf("[ % 2.1f % 2.1f % 2.1f % 2.1f ]   [ % 2.1f ]   [ % 2.1f ]\n", (*m)[0][0], (*m)[0][4], (*m)[0][8], (*m)[0][12], (*u)[0], (*v)[0]);
		printf("[ % 2.1f % 2.1f % 2.1f % 2.1f ]   [ % 2.1f ]   [ % 2.1f ]\n", (*m)[0][1], (*m)[0][5], (*m)[0][9], (*m)[0][13], (*u)[1], (*v)[1]);
		printf("[ % 2.1f % 2.1f % 2.1f % 2.1f ] X [ % 2.1f ] = [ % 2.1f ]\n", (*m)[0][2], (*m)[0][6], (*m)[0][10], (*m)[0][14], (*u)[2], (*v)[2]);
		printf("[ % 2.1f % 2.1f % 2.1f % 2.1f ]   [ % 2.1f ]   [ % 2.1f ]\n", (*m)[0][3], (*m)[0][7], (*m)[0][11], (*m)[0][15], (*u)[3], (*v)[3]);
	}
}


// Prints the multiplication of matrices with each matrix in column major order.
void printMult(Matrix4d* a, Matrix4d* b, Matrix4d* c)
{
	if (debugon)
	{
		printf("[ % 2.1f % 2.1f % 2.1f % 2.1f ]   [ % 2.1f % 2.1f % 2.1f % 2.1f ]   [ % 2.1f % 2.1f % 2.1f % 2.1f ]\n", (*a)[0][0], (*a)[0][4], (*a)[0][8], (*a)[0][12], (*b)[0][0], (*b)[0][4], (*b)[0][8], (*b)[0][12], (*c)[0][0], (*c)[0][4], (*c)[0][8], (*c)[0][12]);
		printf("[ % 2.1f % 2.1f % 2.1f % 2.1f ]   [ % 2.1f % 2.1f % 2.1f % 2.1f ]   [ % 2.1f % 2.1f % 2.1f % 2.1f ]\n", (*a)[0][1], (*a)[0][5], (*a)[0][9], (*a)[0][13], (*b)[0][1], (*b)[0][5], (*b)[0][9], (*b)[0][13], (*c)[0][1], (*c)[0][5], (*c)[0][9], (*c)[0][13]);
		printf("[ % 2.1f % 2.1f % 2.1f % 2.1f ] X [ % 2.1f % 2.1f % 2.1f % 2.1f ] = [ % 2.1f % 2.1f % 2.1f % 2.1f ]\n", (*a)[0][2], (*a)[0][6], (*a)[0][10], (*a)[0][14], (*b)[0][2], (*b)[0][6], (*b)[0][10], (*b)[0][14], (*c)[0][2], (*c)[0][6], (*c)[0][10], (*c)[0][14]);
		printf("[ % 2.1f % 2.1f % 2.1f % 2.1f ]   [ % 2.1f % 2.1f % 2.1f % 2.1f ]   [ % 2.1f % 2.1f % 2.1f % 2.1f ]\n", (*a)[0][3], (*a)[0][7], (*a)[0][11], (*a)[0][15], (*b)[0][3], (*b)[0][7], (*b)[0][11], (*b)[0][15], (*c)[0][3], (*c)[0][7], (*c)[0][11], (*c)[0][15]);
	}
}
