#ifndef BOUNCER_H
#define BOUNCER_H

class Bouncer
{
	public:
		Bouncer();
		void draw();
		void reset();
		void start();
		void stop();
		bool running();
		void rotate(double, double);

//		static const double RT2 = 1.414;  // The square root of 2
		static const double FLOOR = 0;   // Position of the floor (y-coordinate)
		static const double G = -.001;    // Effect of gravity.

	private:
		double colors[6][4];
		double vertexes[6][4][3];

		double pos[3];      // Position of this Bouncer
		double velocity[3]; // x, y, z velocities
		double angle[2];    // The angles showing how much rotation the Bouncer has.
		double a_velocity[3]; // Angular velocity

		double collision[8]; // Points of collision

		bool gravity_works;

		void collide();
		void physics();
		void placeVertexes();
};

#endif
