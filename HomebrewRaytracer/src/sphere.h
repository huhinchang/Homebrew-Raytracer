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
	shared_ptr<Material> _material;
};

bool Sphere::CheckCollision(const Ray& ray, double tMin, double tMax, RaycastHit& hitInfo) const
{
	// uses special quadratic formula when b = 2h
	Vector3 oc = ray.Origin() - _center;
	auto a = ray.Direction().SqrMagnitude();
	auto half_b = Dot(oc, ray.Direction());
	auto c = oc.SqrMagnitude() - _radius * _radius;

	auto discriminant = half_b * half_b - a * c;
	if (discriminant < 0) return false;
	auto sqrtd = sqrt(discriminant);

	// Find the nearest root that lies in the acceptable range.
	auto root = (-half_b - sqrtd) / a;
	if (root < tMin || tMax < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < tMin || tMax < root)
			return false;
	}

	// populate hit record
	hitInfo.t = root;
	hitInfo.Point = ray.At(hitInfo.t);
	Vector3 outward_normal = (hitInfo.Point - _center) / _radius;
	hitInfo.SetNormal(ray, outward_normal);
	hitInfo.Material = _material;

	return true;
}