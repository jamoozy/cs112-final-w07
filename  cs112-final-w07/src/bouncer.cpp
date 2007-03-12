#include <GL/gl.h>
#include <time.h>
#include <stdio.h>
#include "bouncer.h"
#include "geometry.h"
#include "debug.h"

Bouncer::Bouncer() : gravity_works(false)
{
	reset();

	colors[0][0] = 0.8;
	colors[0][1] = 0.8;
	colors[0][2] = 0.8;
	colors[0][3] = 1.0;
	colors[1][0] = 0.8;
	colors[1][1] = 0.0;
	colors[1][2] = 0.0;
	colors[1][3] = 1.0;
	colors[2][0] = 0.0;
	colors[2][1] = 0.8;
	colors[2][2] = 0.0;
	colors[2][3] = 1.0;
	colors[3][0] = 0.0;
	colors[3][1] = 0.0;
	colors[3][2] = 0.8;
	colors[3][3] = 1.0;
	colors[4][0] = 0.0;
	colors[4][1] = 0.8;
	colors[4][2] = 0.8;
	colors[4][3] = 1.0;
	colors[5][0] = 0.8;
	colors[5][1] = 0.0;
	colors[5][2] = 0.8;
	colors[5][3] = 1.0;

	vertexes[0][0][0] = -1.0;
	vertexes[0][0][1] = -1.0;
	vertexes[0][0][2] = -1.0;
	vertexes[0][1][0] = -1.0;
	vertexes[0][1][1] = -1.0;
	vertexes[0][1][2] = 1.0;
	vertexes[0][2][0] = -1.0;
	vertexes[0][2][1] = 1.0;
	vertexes[0][2][2] = 1.0;
	vertexes[0][3][0] = -1.0;
	vertexes[0][3][1] = 1.0;
	vertexes[0][3][2] = -1.0;
	vertexes[1][0][0] = 1.0;
	vertexes[1][0][1] = 1.0;
	vertexes[1][0][2] = 1.0;
	vertexes[1][1][0] = 1.0;
	vertexes[1][1][1] = -1.0;
	vertexes[1][1][2] = 1.0;
	vertexes[1][2][0] = 1.0;
	vertexes[1][2][1] = -1.0;
	vertexes[1][2][2] = -1.0;
	vertexes[1][3][0] = 1.0;
	vertexes[1][3][1] = 1.0;
	vertexes[1][3][2] = -1.0;
	vertexes[2][0][0] = -1.0;
	vertexes[2][0][1] = -1.0;
	vertexes[2][0][2] = -1.0;
	vertexes[2][1][0] = 1.0;
	vertexes[2][1][1] = -1.0;
	vertexes[2][1][2] = -1.0;
	vertexes[2][2][0] = 1.0;
	vertexes[2][2][1] = -1.0;
	vertexes[2][2][2] = 1.0;
	vertexes[2][3][0] = -1.0;
	vertexes[2][3][1] = -1.0;
	vertexes[2][3][2] = 1.0;
	vertexes[3][0][0] = 1.0;
	vertexes[3][0][1] = 1.0;
	vertexes[3][0][2] = 1.0;
	vertexes[3][1][0] = 1.0;
	vertexes[3][1][1] = 1.0;
	vertexes[3][1][2] = -1.0;
	vertexes[3][2][0] = -1.0;
	vertexes[3][2][1] = 1.0;
	vertexes[3][2][2] = -1.0;
	vertexes[3][3][0] = -1.0;
	vertexes[3][3][1] = 1.0;
	vertexes[3][3][2] = 1.0;
	vertexes[4][0][0] = -1.0;
	vertexes[4][0][1] = -1.0;
	vertexes[4][0][2] = -1.0;
	vertexes[4][1][0] = -1.0;
	vertexes[4][1][1] = 1.0;
	vertexes[4][1][2] = -1.0;
	vertexes[4][2][0] = 1.0;
	vertexes[4][2][1] = 1.0;
	vertexes[4][2][2] = -1.0;
	vertexes[4][3][0] = 1.0;
	vertexes[4][3][1] = -1.0;
	vertexes[4][3][2] = -1.0;
	vertexes[5][0][0] = 1.0;
	vertexes[5][0][1] = 1.0;
	vertexes[5][0][2] = 1.0;
	vertexes[5][1][0] = -1.0;
	vertexes[5][1][1] = 1.0;
	vertexes[5][1][2] = 1.0;
	vertexes[5][2][0] = -1.0;
	vertexes[5][2][1] = -1.0;
	vertexes[5][2][2] = 1.0;
	vertexes[5][3][0] = 1.0;
	vertexes[5][3][1] = -1.0;
	vertexes[5][3][2] = 1.0;

	collision[0] = false;
	collision[1] = false;
	collision[2] = false;
	collision[3] = false;
	collision[4] = false;
	collision[5] = false;
	collision[6] = false;
	collision[7] = false;
}

void Bouncer::reset()
{
	gravity_works = false;

	pos[0] = 0;
	pos[1] = 8;
	pos[2] = 0;

	velocity[0] = 0;
	velocity[1] = 0;
	velocity[2] = 0;

	angle[0] = 0;   // angle around y-axis.
	angle[1] = 0;   // angle around x-axis.
}

// Add the given values to the x- and y-roatations.
void Bouncer::rotate(double x, double y)
{
	angle[0] += y;
	angle[1] += x;
}

void Bouncer::start()
{
	gravity_works = true;
}

void Bouncer::stop()
{
	gravity_works = false;

	velocity[0] = 0;
	velocity[1] = 0;
	velocity[2] = 0;
}

bool Bouncer::running()
{
	return gravity_works;
}

//int last_time[] = {0,0,0,0,0,0,0,0};
//bool allow = true;

void Bouncer::collide()
{
//	double factor = (sin(angle[0]) + cos(angle[0])) * (sin(angle[1]) + cos(angle[1]);

	Matrix4d m;
	double M[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, M);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m[i][j] = M[i*4+j];

	Vector4d out;
	Vector4d in;


	int collisions = 0;
	int index = 0;
	for (int i = 1; i >= -1; i -= 2)
		for (int j = 1; j >= -1; j -= 2)
			for (int k = 1; k >= -1; k -= 2, index++)
			{
				in[0] = i;
				in[1] = j;
				in[2] = k;
				in[3] = 1;

				multVector(out, m, in);
//				if (time(0) > 5 + last_time[index]) {
//					printf("%d: Multiplied:\n", index);
//					printMult(&m, &in, &out);
//					last_time[index] = time(0);
//					allow = true;
//				}

				if (out[1] < FLOOR)
				{
//					if (allow) {
//						printf("%2.1f < %d == true\n", out[1], FLOOR);
//						allow = false;
//					}
					collision[index] = true;
					collisions++;
				}
			}


	// Detects collisions and handles them.
//	if (pos[1] - 1 < FLOOR)
//		velocity[1] = -velocity[1];

	if (collisions == 4)
	{
		velocity[1] = -velocity[1];
	}

//	if (collision[0]
//	 || collision[1]
//	 || collision[2]
//	 || collision[3]
//	 || collision[4]
//	 || collision[5]
//	 || collision[6]
//	 || collision[7])
//	{
//		debug("Stopping...\n");
//		stop();
//	}

	collision[0] = collision[1] = collision[2] = collision[3] = collision[4] = collision[5] = collision[6] = collision[7] = false;
	collisions = 0;
}

// Make the physics of the world work.
void Bouncer::physics()
{
	//printf("clock:%d\n", clock());
	// Only execute this 30 time per second
	if (gravity_works) velocity[1] += G;
	pos[0] += velocity[0];
	pos[1] += velocity[1];
	pos[2] += velocity[2];
}


// draw each cube face as an individual polygon
void Bouncer::placeVertexes()
{
	glBegin(GL_QUADS);
	for (int i = 0; i < 6; i++)
	{
		glColor3dv(&colors[i][0]);
		glVertex3dv(&vertexes[i][0][0]);
		glVertex3dv(&vertexes[i][1][0]);
		glVertex3dv(&vertexes[i][2][0]);
		glVertex3dv(&vertexes[i][3][0]);
	}
	glEnd();
}


void Bouncer::draw()
{
	glDisable(GL_BLEND);
	glDisable(GL_POLYGON_SMOOTH);

	// set polygon fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(pos[0], pos[1], pos[2]);
	glRotated(angle[1], 1,0,0);
	glRotated(angle[0], 0,1,0);

	collide();
	physics();
	placeVertexes();

	glPopMatrix();
}