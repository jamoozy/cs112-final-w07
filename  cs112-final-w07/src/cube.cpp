
#include "cube.h"
#include "inputModule.h"

extern int wire;


static float cubeColors[6][4] =
{
	{0.8, 0.8, 0.8, 1.0},
	{0.8, 0.0, 0.0, 1.0},
	{0.0, 0.8, 0.0, 1.0},
	{0.0, 0.0, 0.8, 1.0},
	{0.0, 0.8, 0.8, 1.0},
	{0.8, 0.0, 0.8, 1.0},
};

static float cubeVertexes[6][4][3] =
{
	{
		{-1.0, -1.0, -1.0},
		{-1.0, -1.0, 1.0},
		{-1.0, 1.0, 1.0},
		{-1.0, 1.0, -1.0}},

	{
		{1.0, 1.0, 1.0},
		{1.0, -1.0, 1.0},
		{1.0, -1.0, -1.0},
		{1.0, 1.0, -1.0}},

	{
		{-1.0, -1.0, -1.0},
		{1.0, -1.0, -1.0},
		{1.0, -1.0, 1.0},
		{-1.0, -1.0, 1.0}},

	{
		{1.0, 1.0, 1.0},
		{1.0, 1.0, -1.0},
		{-1.0, 1.0, -1.0},
		{-1.0, 1.0, 1.0}},

	{
		{-1.0, -1.0, -1.0},
		{-1.0, 1.0, -1.0},
		{1.0, 1.0, -1.0},
		{1.0, -1.0, -1.0}},

	{
		{1.0, 1.0, 1.0},
		{-1.0, 1.0, 1.0},
		{-1.0, -1.0, 1.0},
		{1.0, -1.0, 1.0}}
};


void placeVertexes()
{
	for (int i = 0; i < 6; i++)
	{
		if (!wire) glColor3fv(&cubeColors[i][0]);
		glVertex3fv(&cubeVertexes[i][0][0]);
		glVertex3fv(&cubeVertexes[i][1][0]);
		glVertex3fv(&cubeVertexes[i][2][0]);
		glVertex3fv(&cubeVertexes[i][3][0]);
	}
}

void drawCube()
{
	int i;

	if (!wire) {
		glDisable(GL_BLEND);
		glDisable(GL_POLYGON_SMOOTH);

		// set polygon fill mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

		// draw each cube face as an individual polygon
		glBegin(GL_QUADS);
		placeVertexes();
		glEnd();
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
		glBegin(GL_QUADS);
		placeVertexes();
		glEnd();
	}
}
