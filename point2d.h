#ifndef _POINT2D_H
#define _POINT2D_H

class Point2d {
	private:
		int x;
		int y;

	public: 
		Point2d( int = 0, int = 0 );
		~Point2d();

		void X( int );
		void Y( int );

		int X();
		int Y();

		Point2d& operator= ( Point2d );
	};

#endif //_POINT2D_H