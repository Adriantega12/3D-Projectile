#include "projectile.h"

Projectile::Projectile( int x, int y, int z, double ax, double ay, double az )
					: center( x, y, z ), angles( ax, ay, az ), velX( 0 ), velY( 0 ), angX(0), waitTime(180) {
	sides.reserve(4);
	}

Projectile::~Projectile() {

	}

void Projectile::X( int x ) {
	center.X(x);
	}

void Projectile::Y( int y ) {
	center.Y(y);
	}

int Projectile::X() {
	return center.X();
	}

int Projectile::Y() {
	return center.Y();
	}
	
void Projectile::decreaseWaitTime() {
	--waitTime;
	}

void Projectile::VelX( int vx ) {
	velX = vx;
	}

void Projectile::VelY( int vy ) {
	velY = vy;
	}

int Projectile::VelX() {
	return velX;
	}

int Projectile::VelY() {
	return velY;
	}
	
int Projectile::getWaitTime() {
	return waitTime;
	}

void Projectile::setup( double angle ) {
	Point3d frontOrigin, backOrigin;
	front = Point3d( center.X(), center.Y() + DIST_FRONT, center.Z() );
	back = Point3d( center.X(), center.Y() - DIST_BACK, center.Z() );
	sides.push_back(Point3d( center.X(), center.Y(), center.Z() + SIDES_DIST ));
	sides.push_back(Point3d( center.X() - SIDES_DIST / 2, center.Y(), center.Z() + SIDES_DIST / 2 ) );
	sides.push_back(Point3d( center.X() - SIDES_DIST, center.Y(), center.Z() ));
	sides.push_back(Point3d( center.X() - SIDES_DIST / 2, center.Y(), center.Z() - SIDES_DIST / 2 ) );
	sides.push_back(Point3d( center.X(), center.Y(), center.Z() - SIDES_DIST ));
	sides.push_back(Point3d( center.X() + SIDES_DIST / 2, center.Y(), center.Z() - SIDES_DIST / 2 ) );
	sides.push_back(Point3d( center.X() + SIDES_DIST, center.Y(), center.Z() ));
	sides.push_back(Point3d( center.X() + SIDES_DIST / 2, center.Y(), center.Z() + SIDES_DIST / 2 ) );
	
	frontOrigin = Transform::translatePoint( front, -center.X(), -center.Y(), -center.Z() );
	frontOrigin = Transform::rotatePointInZ( frontOrigin, angle );
	front = Transform::translatePoint( frontOrigin, center.X(), center.Y(), center.Z() );
	backOrigin = Transform::translatePoint( back, -center.X(), -center.Y(), -center.Z() );
	backOrigin = Transform::rotatePointInZ( backOrigin, angle );
	back = Transform::translatePoint( backOrigin, center.X(), center.Y(), center.Z() );
	sides = Transform::rotatePointsInZ( sides, angle );
	
	/*int x_c = center.X();
	int y_c = center.Y();
	int rx = front.X() - center.X(),
		ry = center.Y() - front.Y(),
		x = x_c, 
		y = y_c + ry;
	double pk1, pk2;
	
	pk1 = pow( (x - x_c) + 1, 2) * pow(ry, 2) + pow( (y - y_c) - 0.5, 2) * pow(rx, 2) - pow(rx, 2) * pow(ry, 2);
	do {
		// Oct 2
		ellipse.push_back( Point3d( x, y, 0) );
		// Oct 3
		ellipse.push_back( Point3d( x - 2 * (x - x_c), y, 0 ) );

		ellipse.push_back( Point3d( x - 2 * (x - x_c), y - 2 * (y - y_c), 0 ) );
		// Oct 7
		ellipse.push_back( Point3d( x, y - 2 * (y - y_c), 0 ) );
		
		if ( pk1 < 0 ) { // y_k+1 = y_k
			pk1 += pow(ry, 2) * (2 * (x - x_c) + 3);
			}
		else { // y_k+1 = y_k - 1
			pk1 += pow(ry, 2) * (2*(x - x_c) + 3) + pow(rx, 2) * (3 - 2* (y - y_c));
			y--;
			}
		x++;
		}
	while ( 2 * (x - x_c) * pow(ry, 2) < 2 * (y - y_c) * pow(rx, 2) );

	pk2 = pow((x - x_c) + 0.5, 2) * pow(ry, 2) + pow((y - y_c) - 1, 2) * pow(rx, 2) - pow(rx, 2) * pow(ry, 2);
	do {
		// Oct 2
		ellipse.push_back( Point3d( x, y, 0 ) );
		// Oct 3
		ellipse.push_back( Point3d( x - 2 * (x - x_c), y, 0 ) );
		// Oct 6
		ellipse.push_back( Point3d( x - 2 * (x - x_c), y - 2 * (y - y_c), 0 ) );
		// Oct 7
		ellipse.push_back( Point3d( x, y - 2 * (y - y_c), 0 ) );

		if ( pk2 >= 0 ) { // x_k+1 = x_k
			pk2 += pow(rx, 2) - 2 * pow(rx, 2) * ( (y - y_c) - 1);
			}
		else { // x_k+1 = x_k + 1
			pk2 += pow(rx, 2) - 2 * pow(rx, 2) * ( (y - y_c) - 1) + pow(ry, 2) * (2 * (x - x_c) + 1) + pow(ry, 2);
			x++;
			}
		y--;
		}
	while ( y >= y_c );
	
	ellipseZ = Transform::rotatePointsInY(ellipse, 90.0);
	std::copy( ellipseZ.begin(), ellipseZ.end(), ellipse.end());*/
	}

void Projectile::update( int x, int y, double angle ) {
	Point3d frontOrigin, backOrigin, prevCenter = center;

	center.X( x );
	center.Y( y );
	front = Point3d( center.X(), center.Y() + DIST_FRONT, center.Z() );
	back = Point3d( center.X(), center.Y() - DIST_BACK, center.Z() );
	sides[0] = Point3d( center.X(), center.Y(), center.Z() + SIDES_DIST );
	sides[1] = Point3d( center.X() - SIDES_DIST / 2, center.Y(), center.Z() + SIDES_DIST / 2 );
	sides[2] = Point3d( center.X() - SIDES_DIST, center.Y(), center.Z() );
	sides[3] = Point3d( center.X() - SIDES_DIST / 2, center.Y(), center.Z() - SIDES_DIST / 2 );
	sides[4] = Point3d( center.X(), center.Y(), center.Z() - SIDES_DIST );
	sides[5] = Point3d( center.X() + SIDES_DIST / 2, center.Y(), center.Z() - SIDES_DIST / 2 );
	sides[6] = Point3d( center.X() + SIDES_DIST, center.Y(), center.Z() );
	sides[7] = Point3d( center.X() + SIDES_DIST / 2, center.Y(), center.Z() + SIDES_DIST / 2 );
	/*ellipse = Transform::translatePoints( ellipse, prevCenter.X() + (center.X() - prevCenter.X()),
												   prevCenter.Y() + (center.Y() - prevCenter.Y()),
												   prevCenter.Z() + (center.Z() - prevCenter.Z()) );*/ 

	sides = Transform::rotatePointsInY( sides, angles.AngleY() );
	angles.AngleY( angles.AngleY() + 5.0 );

	//std::cout << "Vel X: " << velX << " Vel Y: " << velY << std::endl;
	//std::cout << "X: " << center.X() << " Y: " << center.Y() << std::endl;
	frontOrigin = Transform::translatePoint( front, -center.X(), -center.Y(), -center.Z() );
	frontOrigin = Transform::rotatePointInZ( frontOrigin, angle );
	front = Transform::translatePoint( frontOrigin, center.X(), center.Y(), center.Z() );
	backOrigin = Transform::translatePoint( back, -center.X(), -center.Y(), -center.Z() );
	backOrigin = Transform::rotatePointInZ( backOrigin, angle );
	back = Transform::translatePoint( backOrigin, center.X(), center.Y(), center.Z() );
	sides = Transform::rotatePointsInZ( sides, angle );

	
	/*frontOrigin = Transform::translatePoint( front, -center.X(), -center.Y(), -center.Z() );
	frontOrigin = Transform::rotatePointInX( frontOrigin, angX );
	front = Transform::translatePoint( frontOrigin, center.X(), center.Y(), center.Z() );
	backOrigin = Transform::translatePoint( back, -center.X(), -center.Y(), -center.Z() );
	backOrigin = Transform::rotatePointInX( backOrigin, angX );
	back = Transform::translatePoint( backOrigin, center.X(), center.Y(), center.Z() );*/
	
	}

void Projectile::render( SDL_Renderer*& renderer, Camera& cam ) {
	std::vector<Point2d> sides2d = Transform::project3DTo2D( sides, cam )/*, ellipse2d = Transform::project3DTo2D( ellipse, cam )*/;
	Point2d front2d = Transform::project3DTo2D( front, cam ), 
			back2d = Transform::project3DTo2D( back, cam );

	for (int i = 0; i < sides2d.size(); ++i) {
		gc.drawLine( renderer, front2d.X(), front2d.Y(), 
							   sides2d[i].X(), sides2d[i].Y(), 
					(const Uint8[]){0xFF, 0xFF, 0xFF, 0xFF} );
		gc.drawLine( renderer, back2d.X(), back2d.Y(), 
							   sides2d[i].X(), sides2d[i].Y(), 
					(const Uint8[]){0xFF, 0xFF, 0xFF, 0xFF} );
		}

	for (int i = 0; i < sides2d.size() - 1; ++i) {
		gc.drawLine( renderer, sides2d[i].X(), sides2d[i].Y(), 
							   sides2d[i + 1].X(), sides2d[i + 1].Y(),
					(const Uint8[]){0xFF, 0xFF, 0xFF, 0xFF} );
		}
	gc.drawLine( renderer, sides2d[sides2d.size() - 1].X(), sides2d[sides2d.size() - 1].Y(), 
						   sides2d[0].X(), sides2d[0].Y(),
					(const Uint8[]){0xFF, 0xFF, 0xFF, 0xFF} );
	/*for (int i = 0; i < ellipse2d.size(); ++i) {
		gc.drawRectangle( renderer, ellipse2d[i].X(), ellipse2d[i].Y(), 1, 1, (const Uint8[]){ 0xFF, 0xFF, 0xFF, 0xFF } ); 
		std::cout << ellipse2d[i].X() << " " << ellipse2d[i].Y() << std::endl;
		}*/

	gc.drawRectangle( renderer, front2d.X(), front2d.Y(), 2, 2, (const Uint8[]){0xFF, 0x00, 0x00, 0x00} );
	gc.drawRectangle( renderer, back2d.X(), back2d.Y(), 2, 2, (const Uint8[]){0x00, 0xFF, 0xFF, 0x00} );
	}
