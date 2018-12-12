#include "simulation_state.h"

SimulationState::SimulationState() : proj(-400, Projectile::DIST_BACK, 0), tFrame(0), tFrameAng(0), inc(1) {

	}

SimulationState::~SimulationState() {

	}

void SimulationState::setup() {
	double endX, endY;
	start.X( proj.X() ); 
	start.Y( proj.Y() );
	
	std::cout << "Inserte velocidad: ";
	std::cin >> velocity;
	std::cout << "Inserte ángulo: ";
	std::cin >> angle;

	totalFlightTime = (2 * velocity * sin( Transform::degToRad(angle) ) ) / GRAVITY; // or just (2*Voy) / 9.81
	totalFrames = totalFlightTime * 60 / 1;
	timeStep = totalFlightTime / totalFrames;
	flightTrajectory.reserve( totalFrames );
	endX = ( start.X() + velocity * totalFlightTime * cos( Transform::degToRad( angle ) ) );
	endY = ( start.Y() + velocity * totalFlightTime * sin( Transform::degToRad( angle ) ) - 0.5 * GRAVITY * totalFlightTime * totalFlightTime );

	std::cout << "Total de tiempo en vuelo: " << totalFlightTime << std::endl
			  << "Total de cuadros: " << totalFrames << std::endl
			  << "Tamaño del step: : " << timeStep << std::endl;
		  
	for ( double t = 0; t <= totalFlightTime; t += timeStep ) {
		x = start.X() + velocity * t * cos( Transform::degToRad( angle ) );    // x(t) = v * t * cos(theta)
    	y = start.Y() + velocity * t * sin( Transform::degToRad( angle ) ) - 0.5 * GRAVITY * t * t; // y(t) = v * t * sin(theta) - 0.5*g*(t*t)
		flightTrajectory.push_back( Point2d(round(x), round(y)) );
		if ( Transform::radToDeg( atan( velocity * sin( Transform::degToRad( angle ) ) - GRAVITY * t ) ) > 0 ) {
			angles.push_back( Transform::radToDeg( atan2( y - start.Y(), x - start.X() ) ) + 270.0 );
			}
		else {
			angles.push_back( Transform::radToDeg( atan2( endY - y, endX - x ) ) + 270.0);
			}
		}

	proj.setup( angle + 270.0 );
	bg.setup();
	cam.setCameraPosition( 0, 150, Camera::DIST_FROM_CENTER );
	cam.setCameraAngle( Transform::radToDeg( atan2( cam.Y(), cam.Z() ) ) );
	}

void SimulationState::update() {
	if ( !proj.getWaitTime() ) {
		if ( tFrame < flightTrajectory.size() ) {
			double newAng = angles[tFrame];
			//std::cout << newAng << std::endl;
			proj.update( flightTrajectory[tFrame].X(), flightTrajectory[tFrame].Y(), newAng);
			tFrame++;
			}
		}
	else {
		proj.decreaseWaitTime();
		}
	cam.update();
	}

void SimulationState::render( SDL_Renderer*& renderer ) {
	bg.render( renderer, cam );
	proj.render( renderer, cam );
	}
