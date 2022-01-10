#pragma once

// this header contains the implementation of the sphere class. 
// the funky math is explained in 6.2

#include "RaycastCollider.h"
#include "Vector3.h"

class sphere : public RaycastCollider
{
public:
	sphere() {}
	sphere(point3 cen, double r, shared_ptr<material> m)
		: center(cen), radius(r), mat_ptr(m)
	{
	};

	virtual bool CheckCollision(
		const Ray& r, double t_min, double t_max, RaycastHit& rec) const override;

public:
	point3 center;
	double radius;
	shared_ptr<material> mat_ptr;
};

bool sphere::CheckCollision(const Ray& r, double t_min, double t_max, RaycastHit& rec) const
{
	Vector3 oc = r.origin() - center;
	auto a = r.direction().SqrMagnitude();
	auto half_b = Dot(oc, r.direction());
	auto c = oc.SqrMagnitude() - radius * radius;

	auto discriminant = half_b * half_b - a * c;
	if (discriminant < 0) return false;
	auto sqrtd = sqrt(discriminant);

	// Find the nearest root that lies in the acceptable range.
	auto root = (-half_b - sqrtd) / a;
	if (root < t_min || t_max < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < t_min || t_max < root)
			return false;
	}

	rec.t = root;
	rec.Point = r.At(rec.t);
	rec.Normal = (rec.Point - center) / radius;
	Vector3 outward_normal = (rec.Point - center) / radius;
	rec.SetNormal(r, outward_normal);
	rec.Material = mat_ptr;

	return true;
}