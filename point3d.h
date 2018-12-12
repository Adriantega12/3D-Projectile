#ifndef _POINT3D_H
#define _POINT3D_H

class Point3d {
	protected:
		int x;
		int y;
		int z;

	public:
		Point3d( int = 0, int = 0, int = 0 );
		~Point3d();

		void X( int );
		void Y( int );
		void Z( int );

		int X();
		int Y();
		int Z();

		Point3d& operator= (Point3d);
	};

#endif //_POINT3D_H