#include <GL/gl.h>
#include <time.h>
#include <stdio.h>
#include "bouncer.h"

Bouncer::Bouncer() : gravity_works(false)
{
	reset();

	colors[0][0] = 0.8f;
	colors[0][1] = 0.8f;
	colors[0][2] = 0.8f;
	colors[0][3] = 1.0f;
	colors[1][0] = 0.8f;
	colors[1][1] = 0.0f;
	colors[1][2] = 0.0f;
	colors[1][3] = 1.0f;
	colors[2][0] = 0.0f;
	colors[2][1] = 0.8f;
	colors[2][2] = 0.0f;
	colors[2][3] = 1.0f;
	colors[3][0] = 0.0f;
	colors[3][1] = 0.0f;
	colors[3][2] = 0.8f;
	colors[3][3] = 1.0f;
	colors[4][0] = 0.0f;
	colors[4][1] = 0.8f;
	colors[4][2] = 0.8f;
	colors[4][3] = 1.0f;
	colors[5][0] = 0.8f;
	colors[5][1] = 0.0f;
	colors[5][2] = 0.8f;
	colors[5][3] = 1.0f;

	vertexes[0][0][0] = -1.0f;
	vertexes[0][0][1] = -1.0f;
	vertexes[0][0][2] = -1.0f;
	vertexes[0][1][0] = -1.0f;
	vertexes[0][1][1] = -1.0f;
	vertexes[0][1][2] = 1.0f;
	vertexes[0][2][0] = -1.0f;
	vertexes[0][2][1] = 1.0f;
	vertexes[0][2][2] = 1.0f;
	vertexes[0][3][0] = -1.0f;
	vertexes[0][3][1] = 1.0f;
	vertexes[0][3][2] = -1.0f;
	vertexes[1][0][0] = 1.0f;
	vertexes[1][0][1] = 1.0f;
	vertexes[1][0][2] = 1.0f;
	vertexes[1][1][0] = 1.0f;
	vertexes[1][1][1] = -1.0f;
	vertexes[1][1][2] = 1.0f;
	vertexes[1][2][0] = 1.0f;
	vertexes[1][2][1] = -1.0f;
	vertexes[1][2][2] = -1.0f;
	vertexes[1][3][0] = 1.0f;
	vertexes[1][3][1] = 1.0f;
	vertexes[1][3][2] = -1.0f;
	vertexes[2][0][0] = -1.0f;
	vertexes[2][0][1] = -1.0f;
	vertexes[2][0][2] = -1.0f;
	vertexes[2][1][0] = 1.0f;
	vertexes[2][1][1] = -1.0f;
	vertexes[2][1][2] = -1.0f;
	vertexes[2][2][0] = 1.0f;
	vertexes[2][2][1] = -1.0f;
	vertexes[2][2][2] = 1.0f;
	vertexes[2][3][0] = -1.0f;
	vertexes[2][3][1] = -1.0f;
	vertexes[2][3][2] = 1.0f;
	vertexes[3][0][0] = 1.0f;
	vertexes[3][0][1] = 1.0f;
	vertexes[3][0][2] = 1.0f;
	vertexes[3][1][0] = 1.0f;
	vertexes[3][1][1] = 1.0f;
	vertexes[3][1][2] = -1.0f;
	vertexes[3][2][0] = -1.0f;
	vertexes[3][2][1] = 1.0f;
	vertexes[3][2][2] = -1.0f;
	vertexes[3][3][0] = -1.0f;
	vertexes[3][3][1] = 1.0f;
	vertexes[3][3][2] = 1.0f;
	vertexes[4][0][0] = -1.0f;
	vertexes[4][0][1] = -1.0f;
	vertexes[4][0][2] = -1.0f;
	vertexes[4][1][0] = -1.0f;
	vertexes[4][1][1] = 1.0f;
	vertexes[4][1][2] = -1.0f;
	vertexes[4][2][0] = 1.0f;
	vertexes[4][2][1] = 1.0f;
	vertexes[4][2][2] = -1.0f;
	vertexes[4][3][0] = 1.0f;
	vertexes[4][3][1] = -1.0f;
	vertexes[4][3][2] = -1.0f;
	vertexes[5][0][0] = 1.0f;
	vertexes[5][0][1] = 1.0f;
	vertexes[5][0][2] = 1.0f;
	vertexes[5][1][0] = -1.0f;
	vertexes[5][1][1] = 1.0f;
	vertexes[5][1][2] = 1.0f;
	vertexes[5][2][0] = -1.0f;
	vertexes[5][2][1] = -1.0f;
	vertexes[5][2][2] = 1.0f;
	vertexes[5][3][0] = 1.0f;
	vertexes[5][3][1] = -1.0f;
	vertexes[5][3][2] = 1.0f;
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

bool Bouncer::running()
{
	return gravity_works;
}

void Bouncer::collisions()
{
	// Detects collisions and handles them.
	if (pos[1] - 1 < FLOOR)
		velocity[1] = -velocity[1];
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
	glPushMatrix();
	glTranslated(pos[0], pos[1], pos[2]);
	glRotated(angle[1], 1,0,0);
	glRotated(angle[0], 0,1,0);

	glBegin(GL_QUADS);
	for (int i = 0; i < 6; i++)
	{
		glColor3fv(&colors[i][0]);
		glVertex3fv(&vertexes[i][0][0]);
		glVertex3fv(&vertexes[i][1][0]);
		glVertex3fv(&vertexes[i][2][0]);
		glVertex3fv(&vertexes[i][3][0]);
	}
	glEnd();
	glPopMatrix();
}


void Bouncer::draw()
{
	glDisable(GL_BLEND);
	glDisable(GL_POLYGON_SMOOTH);

	// set polygon fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	collisions();
	physics();
	placeVertexes();

}
