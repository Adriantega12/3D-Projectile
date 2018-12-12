#include "camera.h"

Camera::Camera( int _x, int _y, int _z, double _aX, double _aY, double _aZ )
			: position(_x, _y, _z), angle(_aX, _aY, _aZ), circleStep(0) {

	}

Camera::~Camera() {

	}

void Camera::setCameraPosition( int x, int y, int z ) {
	position.X(x);
	position.Y(y);
	position.Z(z);
	}

void Camera::setCameraAngle( double x, double y, double z ) {
	angle.AngleX(x);
	angle.AngleY(y);
	angle.AngleZ(z);
	}

// Setters
void Camera::X( int x ) {
	position.X(x);
	}

void Camera::Y( int y ) {
	position.Y(y);
	}

void Camera::Z( int z ) {
	position.Z(z);
	}

void Camera::AngleX( double x ) {
	angle.AngleX(x);
	}

void Camera::AngleY( double y ) {
	angle.AngleY(y);
	}

void Camera::AngleZ( double z ) {
	angle.AngleZ(z);
	}

// Getters
int Camera::X() {
	return position.X();
	}

int Camera::Y() {
	return position.Y();
	}

int Camera::Z() {
	return position.Z();
	}

double Camera::AngleX() {
	return angle.AngleX();
	}

double Camera::AngleY() {
	return angle.AngleY();
	}

double Camera::AngleZ() {
	return angle.AngleZ();
	}

void Camera::setup() {

	}

void Camera::update() {
	if ( circleStep < 360 ) {
		position.X( DIST_FROM_CENTER * cos( Transform::degToRad( circleStep ) ) );
        position.Z( DIST_FROM_CENTER * sin( Transform::degToRad( circleStep ) ) );
        ++circleStep;
        angle.AngleY( Transform::radToDeg(atan2( position.X(), position.Z()) ) );
		}

	if ( circleStep == 360 ) {
		circleStep = 0;
		}
	}
