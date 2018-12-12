#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include <cmath>
#include <vector>
#include <iostream>

#include "camera.h"
#include "point2d.h"
#include "point3d.h"

class Camera;

class Transform {
	private:
	public:
		Transform();
		~Transform();

		// Traslación
		static Point3d translatePoint( Point3d, int = 0, int = 0, int = 0 );
		static std::vector<Point3d> translatePoints( std::vector<Point3d>&, int = 0, int = 0, int = 0 );

		// Rotación
		/*
		 * - Las rotaciones son hechas respecto al eje indicado por el nombre de la función.
		 * - El segundo parámetro angle indica el ángulo que va a rotar en sentido horario y en DEG.
		 * - Las rotaciones de múltiples puntos son hechas con el "centroide" del polígono formado
		 *   por el conjunto de puntos y sobre el origen.
		 */
		static Point3d rotatePointInX( Point3d, double );
		static std::vector<Point3d> rotatePointsInX( std::vector<Point3d>&, double );
		static Point3d rotatePointInY( Point3d, double );
		static std::vector<Point3d> rotatePointsInY( std::vector<Point3d>&, double );
		static Point3d rotatePointInZ( Point3d, double );
		static std::vector<Point3d> rotatePointsInZ( std::vector<Point3d>&, double );

		// Escalamiento
		static Point3d scalePoint( Point3d, double = 0.0, double = 0.0, double = 0.0 );
		static std::vector<Point3d> scalePoints( std::vector<Point3d>&, double = 0.0, double = 0.0, double = 0.0 );

		// Proyección
		static Point2d project3DTo2D( Point3d, Camera& );
		static std::vector<Point2d> project3DTo2D( std::vector<Point3d>&, Camera& );

		// Utilería
		static Point3d get3DCentroid( std::vector<Point3d>& );
		static double degToRad( double );
		static double radToDeg( double );
	};

#endif //_TRANSFORM_H