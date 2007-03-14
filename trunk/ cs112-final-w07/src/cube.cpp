#ifdef WIN32
#include <windows.h>
#endif

#include "cube.h"
#include "inputModule.h"

extern int wire;

#define	BACK	0
#define	FRONT	1
#define	LEFT	2
#define	RIGHT	3
#define	BOTTOM	4
#define	TOP		5

#define	X_COOR		0
#define	Y_COOR		1
#define	Z_COOR		2


static float cubeColors[6][4] =
{
	{0.8, 0.8, 0.8, 1.0},
	{0.8, 0.0, 0.0, 1.0},
	{0.0, 0.8, 0.0, 1.0},
	{0.0, 0.0, 0.8, 1.0},
	{0.0, 0.8, 0.8, 1.0},
	{0.8, 0.0, 0.8, 1.0},
};



static float roomVertexes[6][4][3] =
{
	{
		{-2, -2, -2},
		{-2, -2, 2},
		{-2, 2, 2},
		{-2, 2, -2}},

	{
		{2, 2, 2},
		{2, -2, 2},
		{2, -2, -2},
		{2, 2, -2}},

	{
		{-2, -2, -2},
		{2, -2, -2},
		{2, -2, 2},
		{-2, -2, 2}},

	{
		{2, 2, 2},
		{2, 2, -2},
		{-2, 2, -2},
		{-2, 2, 2}},

	{
		{-2, -2, -2},
		{-2, 2, -2},
		{2, 2, -2},
		{2, -2, -2}},

	{
		{2, 2, 2},
		{-2, 2, 2},
		{-2, -2, 2},
		{2, -2, 2}}
};



static float cubeVertexes[6][4][3] =
{
	{
		{-0.3, -0.3, -0.3},
		{-0.3, -0.3, 0.3},
		{-0.3, 0.3, 0.3},
		{-0.3, 0.3, -0.3}},

	{
		{0.3, 0.3, 0.3},
		{0.3, -0.3, 0.3},
		{0.3, -0.3, -0.3},
		{0.3, 0.3, -0.3}},

	{
		{-0.3, -0.3, -0.3},
		{0.3, -0.3, -0.3},
		{0.3, -0.3, 0.3},
		{-0.3, -0.3, 0.3}},

	{
		{0.3, 0.3, 0.3},
		{0.3, 0.3, -0.3},
		{-0.3, 0.3, -0.3},
		{-0.3, 0.3, 0.3}},

	{
		{-0.3, -0.3, -0.3},
		{-0.3, 0.3, -0.3},
		{0.3, 0.3, -0.3},
		{0.3, -0.3, -0.3}},

	{
		{0.3, 0.3, 0.3},
		{-0.3, 0.3, 0.3},
		{-0.3, -0.3, 0.3},
		{0.3, -0.3, 0.3}}
};


typedef float Vector3f[3];
Vector3f cubeRandomvector, revolverRandomvector;

double rangerand(double min, double max, long steps)
{
	return min + ((rand() % steps) * (max - min)) / steps;
}



void moveSpinnerRevolver()
{
	drawRevolver();
	CheckAllCollisions();
	drawCube(); 
	CheckAllCollisions();
	drawRoom(); 
	CheckAllCollisions();

//	Sleep(0);
	glutPostRedisplay();
}


void drawRoom()
{
	// set antialiasingand wire-frame rendering mode 
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(2.5);
	glColor3f(0.0, 0.0, 0.0);

	// draw each cube face as an individual polygon
	for (int i = 0; i < 6; i++) {
		glBegin(GL_POLYGON);
		glVertex3fv(&roomVertexes[i][0][0]);
		glVertex3fv(&roomVertexes[i][1][0]);
		glVertex3fv(&roomVertexes[i][2][0]);
		glVertex3fv(&roomVertexes[i][3][0]);
		glEnd();
	}
}

void drawCube()
{
	//-------------------------------------
	//make the First Cube move randomly
	//-------------------------------------
	static bool firstTime = true;
	if (firstTime)
	{
		cubeRandomvector[0] = 0.02;
		cubeRandomvector[1] = 0.02;
		cubeRandomvector[2] = 0.02;

		firstTime = false;
	}

	for (int i = 0; i < 6; i++) 
	{
		for (int j=0; j<3; j++)
		{
			cubeVertexes[i][0][j] += cubeRandomvector[j];
			cubeVertexes[i][1][j] += cubeRandomvector[j];
			cubeVertexes[i][2][j] += cubeRandomvector[j];
			cubeVertexes[i][3][j] += cubeRandomvector[j];
		}
	}

	if (!wire) {
		glDisable(GL_BLEND);
		glDisable(GL_POLYGON_SMOOTH);

		// set polygon fill mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

		// draw each cube face as an individual polygon
		{
			for (int i = 0; i < 6; i++) {
				glBegin(GL_POLYGON);
				glColor3fv(&cubeColors[i][0]);
				glVertex3fv(&cubeVertexes[i][0][0]);
				glVertex3fv(&cubeVertexes[i][1][0]);
				glVertex3fv(&cubeVertexes[i][2][0]);
				glVertex3fv(&cubeVertexes[i][3][0]);
				glEnd();
			}
		}
	} else {
		// set antialiasingand wire-frame rendering mode 
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_POLYGON_SMOOTH);
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(2.5);
		glColor3f(0.0, 0.0, 0.0);

		// draw each cube face as an individual polygon
		{
			for (int i = 0; i < 6; i++) {
				glBegin(GL_POLYGON);
				glVertex3fv(&cubeVertexes[i][0][0]);
				glVertex3fv(&cubeVertexes[i][1][0]);
				glVertex3fv(&cubeVertexes[i][2][0]);
				glVertex3fv(&cubeVertexes[i][3][0]);
				glEnd();
			}
		}
	}
}




static float revolverColors[6][4] =
{
	{0.18, 0.18, 0.18, 1.0},
	{0.18, 0.0, 0.0, 1.0},
	{0.0, 0.18, 0.0, 1.0},
	{0.0, 0.0, 0.18, 1.0},
	{0.0, 0.18, 0.18, 1.0},
	{0.18, 0.0, 0.18, 1.0},
};

static float revolverVertexes[6][4][3] =
{
	{
		{1, -0.1, -0.1},
		{1, -0.1, 0.1},
		{1, 0.1, 0.1},
		{1, 0.1, -0.1}},

	{
		{1.2, 0.1, 0.1},
		{1.2, -0.1, 0.1},
		{1.2, -0.1, -0.1},
		{1.2, 0.1, -0.1}},

	{
		{1, -0.1, -0.1},
		{1.2, -0.1, -0.1},
		{1.2, -0.1, 0.1},
		{1, -0.1, 0.1}},

	{
		{1.2, 0.1, 0.1},
		{1.2, 0.1, -0.1},
		{1, 0.1, -0.1},
		{1, 0.1, 0.1}},

	{
		{1, -0.1, -0.1},
		{1, 0.1, -0.1},
		{1.2, 0.1, -0.1},
		{1.2, -0.1, -0.1}},

	{
		{1.2, 0.1, 0.1},
		{1, 0.1, 0.1},
		{1, -0.1, 0.1},
		{1.2, -0.1, 0.1}}
};


void drawRevolver()
{
	//-------------------------------------
	//make the Small Cube move randomly
	//-------------------------------------
	static bool firstTime = true;
	if (firstTime)
	{
		revolverRandomvector[0] = 0.02;
		revolverRandomvector[1] = -0.02;
		revolverRandomvector[2] = -0.02;

		firstTime = false;
	}

	for (int i = 0; i < 6; i++) 
	{
		for (int j=0; j<3; j++)
		{
			revolverVertexes[i][0][j] += revolverRandomvector[j];
			revolverVertexes[i][1][j] += revolverRandomvector[j];
			revolverVertexes[i][2][j] += revolverRandomvector[j];
			revolverVertexes[i][3][j] += revolverRandomvector[j];
		}
	}

	//detect collision with the Room or with the Big Cube


	if (!wire) {
		glDisable(GL_BLEND);
		glDisable(GL_POLYGON_SMOOTH);

		// set polygon fill mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

		// draw each cube face as an individual polygon
		{
			for (int i = 0; i < 6; i++) {
				glBegin(GL_POLYGON);
				glColor3fv(&revolverColors[i][0]);
				glVertex3fv(&revolverVertexes[i][0][0]);
				glVertex3fv(&revolverVertexes[i][1][0]);
				glVertex3fv(&revolverVertexes[i][2][0]);
				glVertex3fv(&revolverVertexes[i][3][0]);
				glEnd();
			}
		}
	} else {
		// set antialiasingand wire-frame rendering mode 
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_POLYGON_SMOOTH);
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(2.5);
		glColor3f(0.0, 0.0, 0.0);

		// draw each cube face as an individual polygon
		{
			for (int i = 0; i < 6; i++) {
				glBegin(GL_POLYGON);
				glVertex3fv(&revolverVertexes[i][0][0]);
				glVertex3fv(&revolverVertexes[i][1][0]);
				glVertex3fv(&revolverVertexes[i][2][0]);
				glVertex3fv(&revolverVertexes[i][3][0]);
				glEnd();
			}
		}
	}
}



//-------------------------------------------------------------
//
//-------------------------------------------------------------
void InvertMoveVector(Vector3f& vector)
{
	for (int i=0; i<3; i++)
	{
		vector[i] = -(vector[i]);
	}
}

//-------------------------------------------------------------
//Check collision among all objects in our 3D world
//-------------------------------------------------------------
void CheckAllCollisions()
{
	if (Collide(cubeVertexes, roomVertexes, true))
	{
		InvertMoveVector(cubeRandomvector);
	}

	if (Collide(revolverVertexes, roomVertexes, true))
	{
		InvertMoveVector(revolverRandomvector);
	}

	if (Collide(revolverVertexes, cubeVertexes, false))
	{
		InvertMoveVector(cubeRandomvector);
		InvertMoveVector(revolverRandomvector);
	}

}

//-------------------------------------------------------------
//Check collision between 2 cubes
//-------------------------------------------------------------
bool Collide(GLfloat cube1[6][4][3], GLfloat cube2[6][4][3], bool mustBeInTheBox)
{
	for (int face=BACK; face<FRONT; face++)
	{
		for (int vertex=0; vertex<4; vertex++)
		{
			if (IsVertexInBox(cube1[face][vertex], cube2))
			{
				if (mustBeInTheBox)
					return false;
				else
					return true;
			}
			else
			{
				if (mustBeInTheBox)
					return true;
				else
					return false;
			}
		}
	}

	return false;
}

//-------------------------------------------------------------
//
//-------------------------------------------------------------
//NOTE: check whether a point is within a bounding box
//ADVANTAGE: can be pipelined to boost performance
bool IsVertexInBox(Vector3f vertex, GLfloat cube[6][4][3])
{
	//go through six faces of the cube
	for (int face=BACK; face<TOP; face++)
	{
		for (int coord=0; coord<3; coord++)
		{
			switch (face)
			{
				case BACK:
					//behind the BACK FACE
					if (vertex[0] < cube[face][0][X_COOR])
						return false;
					break;
				case FRONT:
					//infront of the FRONT FACE
					if (vertex[0] > cube[face][0][X_COOR])
						return false;
					break;
				case LEFT:
					//on the left side of the LEFT FACE
					if (vertex[0] < cube[face][0][Y_COOR])
						return false;
					break;
				case RIGHT:
					//on the right side of the RIGHT FACE
					if (vertex[0] > cube[face][0][Y_COOR])
						return false;
					break;
				case BOTTOM:
					//under the BOTTOM FACE
					if (vertex[0] < cube[face][0][Z_COOR])
						return false;
					break;
				case TOP:
					//above the TOP FACE
					if (vertex[0] > cube[face][0][Z_COOR])
						return false;
					break;
			}
		}
	}

	return true;
}
