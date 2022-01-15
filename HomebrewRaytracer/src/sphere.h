#pragma once

// this header contains the implementation of a sphere raycast collider

#include "RaycastCollider.h"
#include "Vector3.h"

class Sphere : public RaycastCollider
{
public:
	Sphere(Point3 center, double radius, shared_ptr<Material> material);
	virtual bool CheckCollision(const Ray& ray, double tMin, double tMax, RaycastHit& hitInfo) const override;

private:
	Point3 _center;
	double _radius;
	shared_ptr<Material> _material;
};