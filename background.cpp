#include "background.h"

Background::Background() {}

Background::~Background() {}

void Background::setup() {
	const int HALF_SIZE = 1200;
	int totalPoints = 120;
	int stepSize = HALF_SIZE / totalPoints;
	for ( int i = -totalPoints; i < totalPoints; i++ ) {
		pointsX1.push_back( Point3d( i * stepSize, 0, HALF_SIZE ) );
		pointsX2.push_back( Point3d( i * stepSize, 0, -HALF_SIZE ) );
		pointsZ1.push_back( Point3d( HALF_SIZE, 0, i * stepSize ) );
		pointsZ2.push_back( Point3d( -HALF_SIZE, 0, i * stepSize ) );
		}
	}

void Background::render( SDL_Renderer*& renderer, Camera& cam ) {
	std::vector<Point2d> pointsX2d1 = Transform::project3DTo2D( pointsX1, cam );
	std::vector<Point2d> pointsX2d2 = Transform::project3DTo2D( pointsX2, cam );
	std::vector<Point2d> pointsZ2d1 = Transform::project3DTo2D( pointsZ1, cam );
	std::vector<Point2d> pointsZ2d2 = Transform::project3DTo2D( pointsZ2, cam );

	for ( int i = 0; i < pointsZ2d1.size(); ++i ) {
		if ( pointsX2d1[i].Y() > 0 and pointsX2d2[i].Y() > 0 and pointsX2d1[i].Y() > 240 and pointsX2d2[i].Y() > 240)
			gc.drawLine( renderer, pointsX2d1[i].X(), pointsX2d1[i].Y(), pointsX2d2[i].X(), pointsX2d2[i].Y(),
						(const Uint8[]){0x00, 0xAA, 0x00, 0xFF} );
		if ( pointsZ2d1[i].Y() > 0 and pointsZ2d2[i].Y() > 0 and pointsZ2d1[i].Y() > 240 and pointsZ2d2[i].Y() > 240 )
			gc.drawLine( renderer, pointsZ2d1[i].X(), pointsZ2d1[i].Y(), pointsZ2d2[i].X(), pointsZ2d2[i].Y(),
						(const Uint8[]){0x00, 0xAA, 0x00, 0xFF} );
		}
	}
