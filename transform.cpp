#include "transform.h"

Transform::Transform() {

	}

Transform::~Transform() {

	}

// Traslación
Point3d Transform::translatePoint( Point3d p, int tx, int ty, int tz ) {
	return Point3d( p.X() + tx, p.Y() + ty, p.Z() + tz );
	}

std::vector<Point3d> Transform::translatePoints( std::vector<Point3d>& pts, int tx, int ty, int tz ) {
	std::vector<Point3d> translatedPts;

	for ( std::vector<Point3d>::iterator p = pts.begin(); p != pts.end(); ++p ) {
		translatedPts.push_back( translatePoint( (*p), tx, ty, tz ) );
		}

	return translatedPts;
	}

// Rotación
/*
 * - Las rotaciones son hechas respecto al eje indicado por el nombre de la función.
 * - El segundo parámetro angle indica el ángulo que va a rotar en sentido horario y en DEG.
 * - Las rotaciones de múltiples puntos son hechas con el "centroide" del polígono formado
 *   por el conjunto de puntos y sobre el origen.
 */
Point3d Transform::rotatePointInX( Point3d p, double angle ) {
	int y = round( p.Y() * cos( degToRad(angle) ) - p.Z() * sin( degToRad( angle ) ) ), 
		z = round( p.Y() * sin( degToRad(angle) ) + p.Z() * cos( degToRad( angle ) ) );

	return Point3d( p.X(), y, z );
	}

std::vector<Point3d> Transform::rotatePointsInX( std::vector<Point3d>& pts, double angle ) {
	std::vector<Point3d> originPts,
						 rotatedOriginPts,
						 rotatedPts;
	Point3d centroid = get3DCentroid( pts );
	
	originPts = translatePoints( pts, - centroid.X(), - centroid.Y(), - centroid.Z() );
	for ( std::vector<Point3d>::iterator p = originPts.begin(); p != originPts.end(); ++p ) {
		rotatedOriginPts.push_back( rotatePointInX( (*p), angle ) );
		}
	rotatedPts = translatePoints( rotatedOriginPts, centroid.X(), centroid.Y(), centroid.Z() );

	return rotatedPts;
	}

Point3d Transform::rotatePointInY( Point3d p, double angle ) {
	int x = round( p.X() * cos( degToRad(angle) ) + p.Z() * sin( degToRad( angle ) ) ), 
		z = round( - p.X() * sin( degToRad(angle) ) + p.Z() * cos( degToRad( angle ) ) );

	return Point3d( x, p.Y(), z );
	}

std::vector<Point3d> Transform::rotatePointsInY( std::vector<Point3d>& pts, double angle ) {
	std::vector<Point3d> originPts,
						 rotatedOriginPts,
						 rotatedPts;
	Point3d centroid = get3DCentroid( pts );
	
	originPts = translatePoints( pts, - centroid.X(), - centroid.Y(), - centroid.Z() );
	for ( std::vector<Point3d>::iterator p = originPts.begin(); p != originPts.end(); ++p ) {
		rotatedOriginPts.push_back( rotatePointInY( (*p), angle ) );
		}
	rotatedPts = translatePoints( rotatedOriginPts, centroid.X(), centroid.Y(), centroid.Z() );

	return rotatedPts;
	}

Point3d Transform::rotatePointInZ( Point3d p, double angle ) {
	int x = round( p.X() * cos( degToRad(angle) ) - p.Y() * sin( degToRad( angle ) ) ), 
		y = round( p.X() * sin( degToRad(angle) ) + p.Y() * cos( degToRad( angle ) ) );

	return Point3d( x, y, p.Z() );
	}

std::vector<Point3d> Transform::rotatePointsInZ( std::vector<Point3d>& pts, double angle ) {
	std::vector<Point3d> originPts,
						 rotatedOriginPts,
						 rotatedPts;
	Point3d centroid = get3DCentroid( pts );
	int i = 0;
	

	originPts = translatePoints( pts, - centroid.X(), - centroid.Y(), - centroid.Z() );

	for ( std::vector<Point3d>::iterator p = originPts.begin(); p != originPts.end(); ++p ) {
		rotatedOriginPts.push_back( rotatePointInZ( (*p), angle ) );
		}
	rotatedPts = translatePoints( rotatedOriginPts, centroid.X(), centroid.Y(), centroid.Z() );

	return rotatedPts;
	}

// Escalamiento
Point3d Transform::scalePoint( Point3d p, double ex, double ey, double ez ) {
	return Point3d( p.X() * ex, p.Y() * ey, p.Z() * ez );
	}

std::vector<Point3d> Transform::scalePoints( std::vector<Point3d>& pts, double ex, double ey, double ez ) {
	std::vector<Point3d> originPts,
						 escaledOriginPts,
						 escaledPts;
	Point3d centroid = get3DCentroid( pts );

	originPts = translatePoints( pts, - centroid.X(), - centroid.Y(), - centroid.Z() );
	for ( std::vector<Point3d>::iterator p = originPts.begin(); p != originPts.end(); ++p ) {
		escaledOriginPts.push_back( scalePoint( (*p), ex, ey, ez ) );
		}
	escaledPts = translatePoints( escaledOriginPts, centroid.X(), centroid.Y(), centroid.Z() );

	return escaledPts;
	}

// Proyección
Point2d Transform::project3DTo2D( Point3d p, Camera& cam ) {
	const int EX = 320;
	const int EY = 240;
	const int EZ = 800;
	int cx = cam.X(), 							// Posición de cámara
		cy = cam.Y(), 
		cz = cam.Z(),
		bx, by; 								// Espacio 2D
	double thetaX = degToRad( cam.AngleX() ), 	// Ángulo de cámara
		   thetaY = degToRad( cam.AngleY() ),
		   thetaZ = degToRad( cam.AngleZ() ),
		   dx, dy, dz; 							// Transformación a espacio de cámara

	// Transformación a espacio de cámara
	dx = cos( thetaY ) * ( sin( thetaZ ) * ( p.Y() - cy ) 
	   + cos( thetaZ ) * ( p.X() - cx ) ) 
	   - sin( thetaY ) * ( p.Z() - cz ); 
	dy = sin( thetaX ) * ( cos( thetaY ) * ( p.Z() - cz ) 
	   + sin( thetaY ) * ( sin( thetaZ ) * ( p.Y() - cy ) 
	   + cos( thetaZ ) * ( p.X() - cx) ) )
	   + cos( thetaX ) * ( cos( thetaZ ) * ( p.Y() - cy ) 
	   - sin( thetaZ ) * ( p.X() - cx) );
	dz = cos( thetaX ) * ( cos( thetaY ) * ( p.Z() - cz ) 
	   + sin( thetaY ) * ( sin( thetaZ ) * ( p.Y() - cy ) 
	   + cos( thetaZ ) * ( p.X() - cx) ) ) 
	   + sin( thetaX ) * ( cos( thetaZ ) * ( p.Y() - cy ) 
	   - sin( thetaZ ) * ( p.X() - cx) );

	// Transformación a plano 2D (Pantalla)
	bx = EZ / dz * dx + EX;
	by = EZ / dz * dy + EY;

	return Point2d( bx, by );
	}

std::vector<Point2d> Transform::project3DTo2D( std::vector<Point3d>& pts, Camera& cam ) {
	const int EX = 320;
	const int EY = 240;
	const int EZ = 800;
	int cx = cam.X(), 							// Posición de cámara
		cy = cam.Y(), 
		cz = cam.Z(),
		bx, by; 								// Espacio 2D
	double thetaX = degToRad( cam.AngleX() ), 	// Ángulo de cámara
		   thetaY = degToRad( cam.AngleY() ),
		   thetaZ = degToRad( cam.AngleZ() ),
		   dx, dy, dz; 							// Transformación a espacio de cámara

	std::vector<Point2d> pts2d;

	for (std::vector<Point3d>::iterator p = pts.begin(); p != pts.end(); ++p) {
		// Transformación a espacio de cámara
		dx = cos( thetaY ) * ( sin( thetaZ ) * ( p->Y() - cy ) 
		   + cos( thetaZ ) * ( p->X() - cx ) ) 
		   - sin( thetaY ) * ( p->Z() - cz ); 
		dy = sin( thetaX ) * ( cos( thetaY ) * ( p->Z() - cz ) 
		   + sin( thetaY ) * ( sin( thetaZ ) * ( p->Y() - cy ) 
		   + cos( thetaZ ) * ( p->X() - cx) ) )
		   + cos( thetaX ) * ( cos( thetaZ ) * ( p->Y() - cy ) 
		   - sin( thetaZ ) * ( p->X() - cx) );
		dz = cos( thetaX ) * ( cos( thetaY ) * ( p->Z() - cz ) 
		   + sin( thetaY ) * ( sin( thetaZ ) * ( p->Y() - cy ) 
		   + cos( thetaZ ) * ( p->X() - cx) ) ) 
		   + sin( thetaX ) * ( cos( thetaZ ) * ( p->Y() - cy ) 
		   - sin( thetaZ ) * ( p->X() - cx) );

		// Transformación a plano 2D (Pantalla)
		bx = EZ / dz * dx + EX;
		by = EZ / dz * dy + EY;

		pts2d.push_back( Point2d( bx, by ) );
		}

	return pts2d;
	}

// Utilería
Point3d Transform::get3DCentroid( std::vector<Point3d>& pts ) {
	int xMin = pts.begin()->X(), 
	    xMax = pts.begin()->X(), 
		yMin = pts.begin()->Y(), 
		yMax = pts.begin()->Y(), 
		zMin = pts.begin()->Z(),
		zMax = pts.begin()->Z();

	for (std::vector<Point3d>::iterator p = pts.begin() + 1; p != pts.end(); ++p) {
		if ( xMin > p->X() ) {
			xMin = p->X();
			}
		if ( xMax < p->X() ) {
			xMax = p->X();
			}
		if ( yMin > p->Y() ) {
			yMin = p->Y();
			}
		if ( yMax < p->Y() ) {
			yMax = p->Y();
			}
		if ( zMin > p->Z() ) {
			zMin = p->Z();
			}
		if ( zMax < p->Z() ) {
			zMax = p->Z();
			}
		}

	return Point3d( (xMax + xMin) / 2, (yMax + yMin) / 2, (zMax + zMin) / 2 );
	}

double Transform::degToRad( double deg ) {
	return M_PI * deg / 180.0;
	}

double Transform::radToDeg( double rad ) {
	return 180.0 * rad / M_PI;
	}
