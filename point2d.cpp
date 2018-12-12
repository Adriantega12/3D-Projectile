#include "point2d.h"

Point2d::Point2d( int _x, int _y ) : x(_x), y(_y) {

	}

Point2d::~Point2d() {
	
	}

void Point2d::X( int _x ) {
	x = _x;
	}

void Point2d::Y( int _y ) {
	y = _y;
	}

int Point2d::X() {
	return x;
	}

int Point2d::Y() {
	return y;
	}

Point2d& Point2d::operator= ( Point2d p ) {
	x = p.x;
	y = p.y;
	return *this;
	}