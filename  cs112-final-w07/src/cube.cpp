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
	{0.8, 0.0, 0.8, 1.0}
};


static float cubeColors1[6][4] =
{
	{0.6, 0, 0.6, 1.0},
	{0.7, 0.8, 0.7, 1.0},
	{0.3, 0.3, 0, 1.0},
	{0.0, 0.0, 0.0, 1.0},
	{0.4, 0.4, 0.4, 1.0},
	{0.3, 0.5, 0, 1.0},
};


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


static float cubeVertexes1[6][4][3] =
{
	{
		{-0.2, -0.2, -0.2},
		{-0.2, -0.2, 0.2},
		{-0.2, 0.2, 0.2},
		{-0.2, 0.2, -0.2}},

	{
		{0.2, 0.2, 0.2},
		{0.2, -0.2, 0.2},
		{0.2, -0.2, -0.2},
		{0.2, 0.2, -0.2}},

	{
		{-0.2, -0.2, -0.2},
		{0.2, -0.2, -0.2},
		{0.2, -0.2, 0.2},
		{-0.2, -0.2, 0.2}},

	{
		{0.2, 0.2, 0.2},
		{0.2, 0.2, -0.2},
		{-0.2, 0.2, -0.2},
		{-0.2, 0.2, 0.2}},

	{
		{-0.2, -0.2, -0.2},
		{-0.2, 0.2, -0.2},
		{0.2, 0.2, -0.2},
		{0.2, -0.2, -0.2}},

	{
		{0.2, 0.2, 0.2},
		{-0.2, 0.2, 0.2},
		{-0.2, -0.2, 0.2},
		{0.2, -0.2, 0.2}}
};

typedef float Vector3f[3];
Vector3f cubeRandomvector,cubeRandomvector1, revolverRandomvector;

double rangerand(double min, double max, long steps)
{
	return min + ((rand() % steps) * (max - min)) / steps;
}



void moveSpinnerRevolver()
{
	static bool isFirstTime = true;
	if (isFirstTime)
	{
		//initialize: separate the cubes (they initially are located at the orginal
		//of the 3D world, so first need to move them apart)
		for (int i=0; i<5; i++)
		{
			drawCube();
			drawRevolver();
		}

		isFirstTime = false;
	}

//	CheckAllCollisions(cubeVertexes, 
//			cubeVertexes1, 
//			revolverVertexes, 
//			roomVertexes);
	drawRevolver();



//	CheckAllCollisions(cubeVertexes, 
//			cubeVertexes1, 
//			revolverVertexes, 
//			roomVertexes);
	drawCube(); 



	CheckAllCollisions(cubeVertexes, 
			cubeVertexes1, 
			revolverVertexes, 
			roomVertexes);
	drawCube1(); 


	drawRoom(); 


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
		cubeRandomvector[0] = 0.0;
		cubeRandomvector[1] = 0.0;
		cubeRandomvector[2] = 0.2;

		/*cubeRandomvector[0] = rangerand(-0.2, 0.2, 10);
		  cubeRandomvector[1] = rangerand(-0.2, 0.2, 10);
		  cubeRandomvector[2] = rangerand(-0.2, 0.2, 10);*/

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


void drawCube1()
{
	//-------------------------------------
	//make the First Cube move randomly
	//-------------------------------------
	static bool firstTime = true;
	if (firstTime)
	{
		cubeRandomvector1[0] = 0.0;
		cubeRandomvector1[1] = -0.0;
		cubeRandomvector1[2] = -0.2;

		firstTime = false;
	}

	for (int i = 0; i < 6; i++) 
	{
		for (int j=0; j<3; j++)
		{
			cubeVertexes1[i][0][j] += cubeRandomvector1[j];
			cubeVertexes1[i][1][j] += cubeRandomvector1[j];
			cubeVertexes1[i][2][j] += cubeRandomvector1[j];
			cubeVertexes1[i][3][j] += cubeRandomvector1[j];
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
				glColor3fv(&cubeColors1[i][0]);
				glVertex3fv(&cubeVertexes1[i][0][0]);
				glVertex3fv(&cubeVertexes1[i][1][0]);
				glVertex3fv(&cubeVertexes1[i][2][0]);
				glVertex3fv(&cubeVertexes1[i][3][0]);
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
				glVertex3fv(&cubeVertexes1[i][0][0]);
				glVertex3fv(&cubeVertexes1[i][1][0]);
				glVertex3fv(&cubeVertexes1[i][2][0]);
				glVertex3fv(&cubeVertexes1[i][3][0]);
				glEnd();
			}
		}
	}
}





void drawRevolver()
{
	//-------------------------------------
	//make the Small Cube move randomly
	//-------------------------------------
	static bool firstTime = true;
	if (firstTime)
	{
		revolverRandomvector[0] = 0.1;
		revolverRandomvector[1] = -0.02;
		revolverRandomvector[2] = -0.01;

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
//change the move vector of a cube each time collision occurs
//-------------------------------------------------------------
void InvertMoveVector(Vector3f& vector, int hitCount, Vector3i faceHit)
{
	for (int i=0;i<hitCount; i++)
	{
		int face = faceHit[i];

		if (face == FRONT)
		{
			vector[X_COOR] = -(vector[X_COOR]);
		}
		else if (face == BACK)
		{
			vector[X_COOR] = -(vector[X_COOR]);
		}
		else if (face == LEFT)
		{
			vector[Y_COOR] = -(vector[Y_COOR]);
		}
		else if (face == RIGHT)
		{
			vector[Y_COOR] = -(vector[Y_COOR]);
		}
		else if (face == BOTTOM)
		{
			vector[Z_COOR] = -(vector[Z_COOR]);
		}
		else if (face == TOP)
		{
			vector[Z_COOR] = -(vector[Z_COOR]);
		}
	}
}

//-------------------------------------------------------------
//Check collision among all objects in our 3D world
//-------------------------------------------------------------
bool CheckAllCollisions(GLfloat TMPcubeVertexes[6][4][3], 
		GLfloat TMPcubeVertexes1[6][4][3], 
		GLfloat TMPrevolverVertexes[6][4][3], 
		GLfloat TMProomVertexes[6][4][3])
{
	Vector3i faceHit;
	bool collided = false;

	//collision between Cube & Room
	int hitCount = Collide(TMPcubeVertexes, TMProomVertexes, true, faceHit);
	if (hitCount > 0)
	{
		collided = true;
		InvertMoveVector(cubeRandomvector, hitCount, faceHit);
	}

	//collision between Cube1 & Room
	hitCount = Collide(TMPcubeVertexes1, TMProomVertexes, true, faceHit);
	if (hitCount > 0)
	{
		collided = true;
		InvertMoveVector(cubeRandomvector1, hitCount, faceHit);
	}

	//collision between Small & Room
	hitCount = Collide(TMPrevolverVertexes, TMProomVertexes, true, faceHit);
	if (hitCount > 0)
	{
		collided = true;
		InvertMoveVector(revolverRandomvector, hitCount, faceHit );
	}

	//collision between Cube & Small
	hitCount = Collide(TMPrevolverVertexes, TMPcubeVertexes, false, faceHit);
	if (hitCount > 0)
	{
		collided = true;
		for (int c=0; c<3; c++)
		{
			cubeRandomvector[c] = -cubeRandomvector[c];
			revolverRandomvector[c] = -revolverRandomvector[c];
		}
	}

	//collision between Cube1 & Small
	hitCount = Collide(TMPrevolverVertexes, TMPcubeVertexes1, false, faceHit);
	if (hitCount > 0)
	{
		collided = true;
		for (int c=0; c<3; c++)
		{
			cubeRandomvector1[c] = -cubeRandomvector1[c];
			revolverRandomvector[c] = -revolverRandomvector[c];
		}
	}

	//collision between Cube & Cube1
	hitCount = Collide(TMPcubeVertexes1, TMPcubeVertexes, false, faceHit);
	if (hitCount > 0)
	{
		collided = true;
		for (int c=0; c<3; c++)
		{
			cubeRandomvector[c] = -cubeRandomvector[c];
			cubeRandomvector1[c] = -cubeRandomvector1[c];
		}
	}
	return collided;
}

//-------------------------------------------------------------
//Check collision between 2 cubes
//-------------------------------------------------------------
int Collide(GLfloat cube1[6][4][3], GLfloat cube2[6][4][3], bool mustBeInTheBox,
		Vector3i& faceHit)
{
	int hitCount = 0;

	for (int face=BACK; face<=FRONT; face++)
	{
		//just need to check 8 vertices in BACK and FRONT faces
		if ((face==BACK) || (face==FRONT))
		{
			for (int vertex=0; vertex<4; vertex++)
			{
				if (mustBeInTheBox)
				{
					//hitCount=0: inside the box
					hitCount = IsVertexInBox(cube1[face][vertex], cube2, faceHit, mustBeInTheBox);
					if (hitCount == 0)
					{
						if (!mustBeInTheBox)
							return hitCount;
					}
					else
					{
						if (mustBeInTheBox)
							return hitCount;
					}
				}
				else
				{
					Vector3f ver;
					ver[0] = cube1[face][vertex][0];
					ver[1] = cube1[face][vertex][1];
					ver[2] = cube1[face][vertex][2];
					if ((	ver[0] > cube2[BACK][0][X_COOR])
							&& (ver[0] < cube2[FRONT][0][X_COOR])
							&& (ver[1] > cube2[BACK][0][Y_COOR])
							&& (ver[1] < cube2[FRONT][0][Y_COOR])
							&& (ver[2] > cube2[BACK][0][Z_COOR])
							&& (ver[2] < cube2[FRONT][0][Z_COOR]))
					{
						faceHit[hitCount++] = face;
						return 1;
					}
				}
			}
		}
	}

	return 0;


}

//-------------------------------------------------------------
//
//-------------------------------------------------------------
//NOTE: check whether a point is within a bounding box
//ADVANTAGE: can be pipelined to boost performance
int IsVertexInBox(Vector3f vertex, GLfloat cube[6][4][3], 
		Vector3i& faceHit, bool mustBeInside)
{
	float x=vertex[0],y=vertex[1],z=vertex[2];
	int hitCount=0;
	//go through six faces of the cube
	for (int face=BACK; face<=TOP; face++)
	{
		switch (face)
		{
			case BACK:
				//behind the BACK FACE
				if ( ((vertex[X_COOR] <= cube[face][0][X_COOR]) && mustBeInside)
						|| ((vertex[X_COOR] > cube[face][0][X_COOR]) && !mustBeInside) )
					faceHit[hitCount++] = face;
				break;
			case FRONT:
				//infront of the FRONT FACE
				if ( ((vertex[X_COOR] >= cube[face][0][X_COOR]) && mustBeInside)
						|| (( vertex[X_COOR] < cube[face][0][X_COOR]) && !mustBeInside) )
					faceHit[hitCount++] = face;
				break;
			case LEFT:
				//on the left side of the LEFT FACE
				if ( ((vertex[Y_COOR] <= cube[face][0][Y_COOR]) && mustBeInside)
						|| (( vertex[Y_COOR] > cube[face][0][Y_COOR]) && !mustBeInside) )
					faceHit[hitCount++] = face;
				break;
			case RIGHT:
				//on the right side of the RIGHT FACE
				if ( ((vertex[Y_COOR] >= cube[face][0][Y_COOR]) && mustBeInside)
						|| ((vertex[Y_COOR] < cube[face][0][Y_COOR]) && !mustBeInside) )
					faceHit[hitCount++] = face;
				break;
			case BOTTOM:
				//under the BOTTOM FACE
				if ( ((vertex[Z_COOR] <= cube[face][0][Z_COOR]) && mustBeInside)
						|| ((vertex[Z_COOR] > cube[face][0][Z_COOR]) && !mustBeInside) )
					faceHit[hitCount++] = face;
				break;
			case TOP:
				//above the TOP FACE
				if ( ((vertex[Z_COOR] >= cube[face][0][Z_COOR]) && mustBeInside)
						|| ((vertex[Z_COOR] < cube[face][0][Z_COOR]) && !mustBeInside) )
					faceHit[hitCount++] = face;
				break;
		}

	}

	return hitCount;

}
