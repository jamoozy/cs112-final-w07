#ifdef _WIN32
#include <windows.h>
#endif
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include <math.h>
#include <time.h>
#include <stdio.h>
#include "bouncer.h"
#include "geometry.h"
#include "debug.h"

const double Bouncer::FLOOR = -5;  // y-coord of the floor.
const double Bouncer::G = -.001;   // gravity.
const double Bouncer::I = 1/3;     // moment of inertia

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

	faces[0][0] = 7;
	faces[0][1] = 6;
	faces[0][2] = 4;
	faces[0][3] = 5;
	faces[1][0] = 0;
	faces[1][1] = 2;
	faces[1][2] = 3;
	faces[1][3] = 1;
	faces[2][0] = 7;
	faces[2][1] = 3;
	faces[2][2] = 2;
	faces[2][3] = 6;
	faces[3][0] = 0;
	faces[3][1] = 1;
	faces[3][2] = 5;
	faces[3][3] = 4;
	faces[4][0] = 7;
	faces[4][1] = 5;
	faces[4][2] = 1;
	faces[4][3] = 3;
	faces[5][0] = 0;
	faces[5][1] = 4;
	faces[5][2] = 6;
	faces[5][3] = 2;

	vertexes[0][0] = 1.0f;
	vertexes[0][1] = 1.0f;
	vertexes[0][2] = 1.0f;
	vertexes[1][0] = 1.0f;
	vertexes[1][1] = 1.0f;
	vertexes[1][2] = -1.0f;
	vertexes[2][0] = 1.0f;
	vertexes[2][1] = -1.0f;
	vertexes[2][2] = 1.0f;
	vertexes[3][0] = 1.0f;
	vertexes[3][1] = -1.0f;
	vertexes[3][2] = -1.0f;
	vertexes[4][0] = -1.0f;
	vertexes[4][1] = 1.0f;
	vertexes[4][2] = 1.0f;
	vertexes[5][0] = -1.0f;
	vertexes[5][1] = 1.0f;
	vertexes[5][2] = -1.0f;
	vertexes[6][0] = -1.0f;
	vertexes[6][1] = -1.0f;
	vertexes[6][2] = 1.0f;
	vertexes[7][0] = -1.0f;
	vertexes[7][1] = -1.0f;
	vertexes[7][2] = -1.0f;

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
	pos[1] = 5;
	pos[2] = 0;

	velocity[0] = 0;
	velocity[1] = 0;
	velocity[2] = 0;

	angle[0] = 0;   // angle around x-axis.
	angle[1] = 0;   // angle around y-axis.
	angle[2] = 0;   // angle around z-axis.

	a_velocity[0] = 0;
	a_velocity[1] = 0;
	a_velocity[2] = 0;
}

// Add the given values to the x- and y-roatations.
void Bouncer::rotate(double x, double y)
{
	angle[0] += x;
	angle[1] += y;
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

	a_velocity[0] = 0;
	a_velocity[1] = 0;
	a_velocity[2] = 0;
}

bool Bouncer::running()
{
	return gravity_works;
}

//int last_time[] = {0,0,0,0,0,0,0,0};
//bool allow = true;

void Bouncer::collide()
{
	trace(__FILE__,__LINE__,"Bouncer::collide()\n",1);

	Matrix4d m;
	double M[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, M);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m[i][j] = M[i*4+j];

	Vector4d out = {0,0,0,1};
	Vector4d in  = {0,0,0,1};

	int collisions = 0;
	int index = 0;
	for (int i = 1; i >= -1; i -= 2)
		for (int j = 1; j >= -1; j -= 2)
			for (int k = 1; k >= -1; k -= 2, index++)
			{
				in[0] = i;
				in[1] = j;
				in[2] = k;

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

	if (collisions) printf("%d collisions\n", collisions);
	if (collisions == 4)
	{
		if (debugon) printf("y-speed: %.4f\n", velocity[1]);
		if (-0.005 < velocity[1]) {
			stop();
			pos[1] = Bouncer::FLOOR + 1;
		} else
			velocity[1] = -velocity[1];
	}
	else if (collisions == 2)
	{
		int i, v[2];

		for (i = 0; i < 8; i++)
			if (collision[i])
			{
				v[0] = i;
				break;
			}

		for (i++; i < 8; i++)
			if (collision[i])
			{
				v[1] = i;
				break;
			}

		Vector4d vertex, center;
		in[0] = vertexes[v[0]][0];
		in[1] = vertexes[v[0]][1];
		in[2] = vertexes[v[0]][2];
		multVector(vertex, m, in);

		in[0] = in[1] = in[2] = 0;
		multVector(center, m, in);

		if (vertexes[v[0]][0] != vertexes[v[1]][0])
		{
			debug("Along x-axis.\n");

			double dy = center[1] - vertex[1];
			double dz = center[2] - vertex[2];

			a_velocity[0] += cos(angle[1]) * dz / 1.414;
			a_velocity[2] += sin(angle[1]) * dz / 1.414;
			velocity[1] *= -(dy / 1.414);
			velocity[2] += (dz / 40);
		}
		else if (vertexes[v[0]][1] != vertexes[v[1]][1])
		{
			debug("Along y-axis.\n");

			double dx = center[0] - vertex[0];
			double dy = center[1] - vertex[1];

			a_velocity[1] -= cos(angle[2]) * dx / 1.414;
			a_velocity[0] -= sin(angle[2]) * dx / 1.414;
			velocity[1] *= -(dy / 1.414);
			velocity[0] += (dx / 40);
		}
		else if (vertexes[v[0]][2] != vertexes[v[1]][2])
		{
			debug("Along z-axis.\n");

			double dy = center[1] - vertex[1];
			double dz = center[2] - vertex[2];

			a_velocity[2] += cos(angle[1]) * dz / 1.414;
			a_velocity[0] += sin(angle[1]) * dz / 1.414;
			velocity[1] *= -(dy / 1.414);
			velocity[2] += (dz / 40);

			if (debugon) printf("a-v{z}: %1.4f\nangle: %1.4f\n", a_velocity[2], angle[2]);
		}
		else
		{
			debug("Along no axis???\n");

			if (debugon)
			{
				printf("%2.1f,%2.1f,%2.1f\n",vertexes[v[0]][0],vertexes[v[0]][0],vertexes[v[0]][0]);
				printf("%2.1f,%2.1f,%2.1f\n",vertexes[v[1]][0],vertexes[v[1]][0],vertexes[v[1]][0]);
			}
		}
	}
	else if (collisions == 1)
	{
		int i, v;

		for (i = 0; i < 8; i++)
			if (collision[i])
			{
				v = i;
				break;
			}

		Vector4d vertex, center;
		in[0] = vertexes[v][0];
		in[1] = vertexes[v][1];
		in[2] = vertexes[v][2];
		multVector(vertex, m, in);

		in[0] = in[1] = in[2] = 0;
		multVector(center, m, in);
	}

	collision[0] = collision[1] = collision[2] = collision[3] = collision[4] = collision[5] = collision[6] = collision[7] = false;
	collisions = 0;
	trace(__FILE__,__LINE__,"~Bouncer::collide()\n",-1);
}

// Make the physics of the world work.
void Bouncer::physics()
{
	trace(__FILE__,__LINE__,"Bouncer::phyics()\n",1);
	//printf("clock:%d\n", clock());
	// Only execute this 30 time per second
	if (gravity_works) velocity[1] += G;

	pos[0] += velocity[0];
	pos[1] += velocity[1];
	pos[2] += velocity[2];

	angle[0] += a_velocity[0];
	angle[1] += a_velocity[1];
	angle[2] += a_velocity[2];

	trace(__FILE__,__LINE__,"~Bouncer::phyics()\n",-1);
}


// draw each cube face as an individual polygon
void Bouncer::placeVertexes()
{
	glBegin(GL_QUADS);
	for (int i = 0; i < 6; i++)
	{
		glColor3dv(&colors[i][0]);
		glVertex3dv(&vertexes[faces[i][0]][0]);
		glVertex3dv(&vertexes[faces[i][1]][0]);
		glVertex3dv(&vertexes[faces[i][2]][0]);
		glVertex3dv(&vertexes[faces[i][3]][0]);
	}
	glEnd();
}


void Bouncer::draw()
{
	trace(__FILE__,__LINE__,"Bouncer::draw()\n",1);

	glDisable(GL_BLEND);
	glDisable(GL_POLYGON_SMOOTH);

	// set polygon fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslated(pos[0], pos[1], pos[2]);
	glRotated(angle[0], 1,0,0);
	glRotated(angle[1], 0,1,0);
	glRotated(angle[2], 0,0,1);
//	glScaled(5,5,5);

	collide();
	physics();
	placeVertexes();

	glPopMatrix();

	trace(__FILE__,__LINE__,"~Bouncer::draw()\n",-1);
}
