#ifndef _ORIENTATION_H
#define _ORIENTATION_H

class Orientation {
	private:
		double angleX;
		double angleY;
		double angleZ;

	public:
		Orientation( double = 0.0, double = 0.0, double = 0.0 );
		~Orientation();

		// Setters
		void AngleX( double );
		void AngleY( double );
		void AngleZ( double );

		// Getters
		double AngleX();
		double AngleY();
		double AngleZ();
	};

#endif //_ORIENTATION_H