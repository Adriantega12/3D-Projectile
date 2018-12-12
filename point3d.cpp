#include "point3d.h"

Point3d::Point3d( int _x, int _y, int _z ) : x(_x), y(_y), z(_z) {

	}

Point3d::~Point3d() {

	}

void Point3d::X( int _x ) {
	x = _x;
	}

void Point3d::Y( int _y ) {
	y = _y;
	}

void Point3d::Z( int _z ) {
	z = _z;
	}

int Point3d::X() {
	return x;
	}

int Point3d::Y() {
	return y;
	}

int Point3d::Z() {
	return z;
	}

Point3d& Point3d::operator=(Point3d p ) {
	x = p.x;
	y = p.y;
	z = p.z;
	return *this;
	}