#pragma once

// this class manages the virtual camera and the related tasks of scene sampling

#include "Utils.h"
#include "Vector3.h"
#include "Ray.h"

class Camera
{
public:
	Camera(
		Point3 lookfrom,
		Point3 lookat,
		Vector3 vup,
		double vfov, // vertical field-of-view in degrees
		double aspect_ratio,
		double aperture,
		double focus_dist
	);

	// returns a ray from the camera to the viewport coordinates
	Ray ViewportToRay(double s, double t) const;

private:
	Point3 origin;
	Point3 lower_left_corner;
	Vector3 horizontal;
	Vector3 vertical;

	Vector3 u, v, w;
	double lens_radius;
};