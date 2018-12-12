#ifndef _BACKGROUND_H
#define _BACKGROUND_H

#include "graphics_component.h"
#include "point3d.h"
#include "camera.h"
#include "transform.h"

class Background {
	private:
		GraphicsComponent gc;
		std::vector<Point3d> pointsX1;
		std::vector<Point3d> pointsZ1;
		std::vector<Point3d> pointsX2;
		std::vector<Point3d> pointsZ2;

	public:
		Background();
		~Background();

		void setup();
		void render( SDL_Renderer*&, Camera& );
	};

#endif //_BACKGROUND_H