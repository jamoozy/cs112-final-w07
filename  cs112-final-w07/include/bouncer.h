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
		static const double FLOOR;   // Position of the floor (y-coordinate)
		static const double G;    // Effect of gravity.

	private:
		double colors[6][4];
		double vertexes[8][3]; // 8 vertexes with 3 coordinates each.
		int faces[6][4];    // 6 faces w/ 4 vertecies each.
		                    // Instead of storing the coordinates
							// of the vertexes, it stores the index
							// of the vertex.

		double pos[3];        // Position of this Bouncer
		double velocity[3];   // x, y, z velocities
		double angle[3];      // The angles showing how much rotation the Bouncer has.
		double a_velocity[3]; // Angular velocity

		double collision[8];  // Points of collision

		bool gravity_works;

		void collide();
		void physics();
		void placeVertexes();
};

#endif
