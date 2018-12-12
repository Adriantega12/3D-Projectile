#ifndef _CAMERA_H
#define _CAMERA_H

#include <vector>
#include <cmath>

#include "point3d.h"
#include "orientation.h"
#include "transform.h"

class Camera {
	private:

		Point3d position;
		Orientation angle;
		int circleStep;

		std::vector<Point3d> route;

	public:
		static const int DIST_FROM_CENTER = 1200;

		Camera( int = 0, int = 0, int = 0, double = 0.0, double = 0.0, double = 0.0 );
		~Camera();

		void setCameraPosition( int = 0, int = 0, int = 0 );
		void setCameraAngle( double = 0.0, double = 0.0, double = 0.0 );

		// Setters
		void X( int );
		void Y( int );
		void Z( int );
		void AngleX( double );
		void AngleY( double );
		void AngleZ( double );

		// Getters
		int X();
		int Y();
		int Z();
		double AngleX();
		double AngleY();
		double AngleZ();

		void setup();
		void update();

	};

#endif //_CAMERA_H