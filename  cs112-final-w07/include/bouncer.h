#ifndef BOUNCER_H
#define BOUNCER_H

class Bouncer
{
	public:
		Bouncer();
		void draw();
		void reset();
		void start();
		bool running();
		void rotate(double, double);
		static const float FLOOR = -8;  // Position of the floor (y-coordinate)
		static const float G = -.001;      // Effect of gravity.

	private:
		float colors[6][4];
		float vertexes[6][4][3];

		float pos[3];      // Position of this Bouncer
		float velocity[3]; // x, y, z velocities
		double angle[2];   // The angles showing how much rotation the Bouncer has.

		bool gravity_works;

		void collisions();
		void physics();
		void placeVertexes();
};

#endif
