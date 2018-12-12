#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "point3d.h"
#include "point2d.h"
#include "orientation.h"
#include "transform.h"
#include "graphics_component.h"

class Projectile {
	private:
		

		// Physics
		Point3d initPos;
		Point3d center;
		Orientation angles;
		int velX;
		int velY;
		double angX;
		int waitTime;

		// Gráficos
		GraphicsComponent gc;

		// Puntos
		Point3d front;
		Point3d back;
		std::vector<Point3d> sides;
		std::vector<Point3d> ellipse;

	public:
		static const int DIST_FRONT = 50;
		static const int DIST_BACK = 50;
		static const int SIDES_DIST = 30;
		
		Projectile( int = 0, int = 0, int = 0, double = 0.0, double = 0.0, double = 0.0 );
		~Projectile();

		void X( int );
		void Y( int );
		void VelX( int ); 
		void VelY( int ); 
		void decreaseWaitTime();

		int X();
		int Y();
		int VelX(); 
		int VelY();
		int getWaitTime();

		void setup( double = 0.0 );
		void update( int, int, double = 0.0 );
		void render( SDL_Renderer*&, Camera& );
	};

#endif
