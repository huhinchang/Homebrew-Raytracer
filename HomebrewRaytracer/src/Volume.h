#pragma once

// this header contains the implementation of a volume raycast collider (to be used with the fog material)

#include "Vector3.h"
#include "Sphere.h"

class Volume : public RaycastCollider
{
public:
	Volume(Point3 center, double radius, shared_ptr<Material> material, double density)
		: _center{ center }, _radius{ radius }, _material{ material }, _density{ Clamp(density, 0, infinity) }
	{
	};

	virtual bool CheckCollision(const Ray& ray, double tMin, double tMax, RaycastHit& hitInfo) const override;

private:
	Point3 _center;
	double _radius;
	shared_ptr<Material> _material;
	double _density;
};

bool Volume::CheckCollision(const Ray& ray, double tMin, double tMax, RaycastHit& hitInfo) const
{
	/*
		RaycastHit initialHitInfo;
		if (!Sphere::CheckCollision(ray, tMin, tMax, initialHitInfo))
		{
			return false;
		}

		if (!initialHitInfo.IsNormalOutward)
		{
			return false;
		}

		// ray intersects sphere. fire another ray through the sphere
		RaycastHit penetrateHitInfo;
		if (Sphere::CheckCollision(Ray(initialHitInfo.Point + ray.Direction() * 0.0001, ray.Direction()), tMin, tMax, penetrateHitInfo))
		{
			if ((penetrateHitInfo.Point - initialHitInfo.Point).Magnitude() * _density > RandomDouble())
			{
				hitInfo.Point = Lerp(hitInfo.Point, penetrateHitInfo.Point, RandomDouble());
				hitInfo.Material = _material;
				hitInfo.Normal = Vector3(1, 0, 0);
				hitInfo.t = (hitInfo.Point - penetrateHitInfo.Point).Magnitude();
				hitInfo.IsNormalOutward = false;
				return true;
			}
		}

		return false;
		*/

		// uses special quadratic formula when b = 2h
	Vector3 oc = ray.Origin() - _center;
	auto a = ray.Direction().SqrMagnitude();
	auto half_b = Dot(oc, ray.Direction());
	auto c = oc.SqrMagnitude() - _radius * _radius;

	auto discriminant = half_b * half_b - a * c;
	if (discriminant <= 0) return false;
	auto sqrtd = sqrt(discriminant);

	// Find the nearest root that lies in the acceptable range.
	auto closeRoot = (-half_b - sqrtd) / a;
	auto farRoot = (-half_b + sqrtd) / a;

	if (farRoot < closeRoot || tMax < closeRoot)
	{
		return false;
	}
	if (closeRoot < tMin || tMax < closeRoot)
	{
		closeRoot = tMin;
	}
	if (tMax < farRoot)
	{
		farRoot = tMax;
	}

	if ((farRoot - closeRoot) * _density > RandomDouble())
	{
		hitInfo.t = farRoot;
		hitInfo.Point = ray.At(hitInfo.t);
		hitInfo.Material = _material;
		hitInfo.Normal = Vector3(1, 0, 0);
		hitInfo.IsNormalOutward = false;
		return true;
	}

	return false;
}
