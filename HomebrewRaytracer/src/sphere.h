#pragma once

// this header contains the implementation of a sphere raycast collider

#include "RaycastCollider.h"
#include "Vector3.h"

class Sphere : public RaycastCollider
{
public:
	Sphere(point3 center, double radius, shared_ptr<Material> material)
		: _center{ center }, _radius{ radius }, _material{ material }
	{
	};

	virtual bool CheckCollision(const Ray& ray, double tMin, double tMax, RaycastHit& hitInfo) const override;

private:
	point3 _center;
	double _radius;
protected:
	shared_ptr<Material> _material;
};

bool Sphere::CheckCollision(const Ray& r, double t_min, double t_max, RaycastHit& hitInfo) const
{
	// uses special quadratic formula when b = 2h
	Vector3 oc = r.Origin() - _center;
	auto a = r.Direction().SqrMagnitude();
	auto half_b = Dot(oc, r.Direction());
	auto c = oc.SqrMagnitude() - _radius * _radius;

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

	// populate hit record
	hitInfo.t = root;
	hitInfo.Point = r.At(hitInfo.t);
	Vector3 outward_normal = (hitInfo.Point - _center) / _radius;
	hitInfo.SetNormal(r, outward_normal);
	hitInfo.Material = _material;

	return true;
}