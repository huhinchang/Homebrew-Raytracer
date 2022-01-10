#pragma once

// this header contains a abstract class to be inherited by all objects that should
// intercept raycasts.

#include "Ray.h"
#include "Utils.h"

class Material;

struct RaycastHit
{
	point3 Point;
	Vector3 Normal;
	shared_ptr<Material> Material;
	double t;
	bool IsNormalOutward; // normals always point against ray

	inline void SetNormal(const Ray& ray, const Vector3& outwardNormal)
	{
		IsNormalOutward = Dot(ray.Direction(), outwardNormal) < 0;
		Normal = IsNormalOutward ? outwardNormal : -outwardNormal;
		Normal = Normalized(Normal);
	}
};

class RaycastCollider
{
public:
	// checks if ray collides with this collider, and the t value is between tmin and tmax
	virtual bool CheckCollision(const Ray& ray, double tMin, double tMax, RaycastHit& hitInfo) const = 0;
};