#ifndef _SIMULATION_STATE_H
#define _SIMULATION_STATE_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#include "camera.h"
#include "projectile.h"
#include "transform.h"
#include "sdl_graphics.h"
#include "background.h"

class SimulationState {
	private:

		// Simulación
		Camera cam;
        Projectile proj;
        Background bg;

        Point2d start;
        Point2d end;

        // Simulación
        double x;
        double y;
        double velocity;
        double timeStep;
        double angle;
        double totalFlightTime;
        int totalFrames;
        int inc;

        int tFrame;
        int tFrameAng;
        std::vector<Point2d> flightTrajectory;
        std::vector<double> angles;

	public:
		static constexpr double GRAVITY = 9.81; // Redondeado para poder trabajar con enteros.


		SimulationState();
		~SimulationState();

		void setup();
		void update();
		void render( SDL_Renderer*& );
	};

#endif //_SIMULATION_STATE_H