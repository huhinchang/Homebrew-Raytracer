#pragma once

// this header contains the implementation of a volume raycast collider (to be used with the fog material)

#include "Vector3.h"
#include "RaycastCollider.h"

class Volume : public RaycastCollider
{
public:
	Volume(Point3 center, double radius, shared_ptr<Material> material, double density);

	virtual bool CheckCollision(const Ray& ray, double tMin, double tMax, RaycastHit& hitInfo) const override;

private:
	Point3 _center;
	double _radius;
	shared_ptr<Material> _material;
	double _density;
};