#include "orientation.h"

#include "orientation.h"

Orientation::Orientation( double x, double y, double z ) 
						: angleX(x), angleY(y), angleZ(z) {

	}

Orientation::~Orientation() {

	}

// Setters
void Orientation::AngleX( double x ) {
	angleX = x;
	}

void Orientation::AngleY( double y ) {
	angleY = y;
	}

void Orientation::AngleZ( double z ) {
	angleZ = z;
	}

// Getters
double Orientation::AngleX() {
	return angleX;
	}

double Orientation::AngleY() {
	return angleY;
	}

double Orientation::AngleZ() {
	return angleZ;
	}