#pragma once

// this class manages the virtual camera and the related tasks of scene sampling

#include "Utils.h"

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
	)
	{
		auto theta = Deg2Rad(vfov);
		auto h = tan(theta / 2);
		auto viewport_height = 2.0 * h;
		auto viewport_width = aspect_ratio * viewport_height;

		w = Normalized(lookfrom - lookat);
		u = Normalized(Cross(vup, w));
		v = Cross(w, u);

		origin = lookfrom;
		horizontal = focus_dist * viewport_width * u;
		vertical = focus_dist * viewport_height * v;
		lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_dist * w;

		lens_radius = aperture / 2;
	}

	// returns a ray from the camera to the viewport coordinates
	Ray ViewportToRay(double s, double t) const
	{
		Vector3 rd = lens_radius * RandomInUnitDisk();
		Vector3 offset = u * rd.x + v * rd.y;

		return Ray(
			origin + offset,
			lower_left_corner + s * horizontal + t * vertical - origin - offset
		);
	}

private:
	Point3 origin;
	Point3 lower_left_corner;
	Vector3 horizontal;
	Vector3 vertical;

	Vector3 u, v, w;
	double lens_radius;
};