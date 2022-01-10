#pragma once

// this class manages the virtual camera and the related tasks of scene sampling

#include "rtweekend.h"

class camera
{
public:
	camera(
		point3 lookfrom,
		point3 lookat,
		Vector3   vup,
		double vfov, // vertical field-of-view in degrees
		double aspect_ratio,
		double aperture,
		double focus_dist
	)
	{
		auto theta = degrees_to_radians(vfov);
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
	ray get_ray(double s, double t) const
	{
		Vector3 rd = lens_radius * random_in_unit_disk();
		Vector3 offset = u * rd.x + v * rd.y;

		return ray(
			origin + offset,
			lower_left_corner + s * horizontal + t * vertical - origin - offset
		);
	}

private:
	point3 origin;
	point3 lower_left_corner;
	Vector3 horizontal;
	Vector3 vertical;

	Vector3 u, v, w;
	double lens_radius;
};