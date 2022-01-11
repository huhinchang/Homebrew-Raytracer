#pragma once

// this header contains the implementation of a volume raycast collider (to be used with the fog material)

#include "Vector3.h"
#include "Sphere.h"

class Volume : public Sphere
{
public:
	Volume(point3 center, double radius, shared_ptr<Material> material, double density)
		: Sphere(center, radius, material), _density{ Clamp(density, 0, infinity) }
	{
	};

	virtual bool CheckCollision(const Ray& ray, double tMin, double tMax, RaycastHit& hitInfo) const override;

private:
	double _density;
};

bool Volume::CheckCollision(const Ray& ray, double tMin, double tMax, RaycastHit& hitInfo) const
{
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
	if (!Sphere::CheckCollision(Ray(initialHitInfo.Point + ray.Direction() * 0.0001, ray.Direction()), tMin, tMax, penetrateHitInfo))
	{
		std::cerr << "penetrating ray didn't hit anything!" << std::endl;
	}

	if ((penetrateHitInfo.Point - initialHitInfo.Point).Magnitude() * _density > RandomDouble())
	{
		hitInfo.Point = Lerp(hitInfo.Point, penetrateHitInfo.Point, RandomDouble());
		hitInfo.t = (hitInfo.Point - penetrateHitInfo.Point).Magnitude();
		hitInfo.Normal = Vector3(1, 0, 0);
		hitInfo.IsNormalOutward = false;
		hitInfo.Material = _material;
		return true;
	}

	/*
	if (RandomDouble() > (outHitInfo.Point - hitInfo.Point).Magnitude() * _density)
	{
		hitInfo.Point = Lerp(hitInfo.Point, outHitInfo.Point, RandomDouble());
		hitInfo.t = (hitInfo.Point - outHitInfo.Point).Magnitude();
		hitInfo.Normal = Vector3(1, 0, 0);
	}
	*/

	return false;
}
