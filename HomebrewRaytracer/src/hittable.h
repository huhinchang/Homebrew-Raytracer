#pragma once

// this header contains a abstract class to be inherited by all objects that should
// intercept raycasts.

#include "ray.h"
#include "Utils.h"

class material;

struct hit_record
{
	point3 p;
	Vector3 normal;
	shared_ptr<material> mat_ptr;
	double t;
	bool front_face;

	inline void set_face_normal(const ray& r, const Vector3& outward_normal)
	{
		front_face = Dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

class hittable
{
public:
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};