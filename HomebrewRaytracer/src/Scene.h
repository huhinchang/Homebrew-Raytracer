#pragma once

// this header contains abstract class that manages all hittables

#include "RaycastCollider.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class Scene : public RaycastCollider
{
public:
	Scene() {}
	Scene(shared_ptr<RaycastCollider> raycastCollider) { AddCollider(raycastCollider); }

	void Clear() { objects.clear(); }
	void AddCollider(shared_ptr<RaycastCollider> raycastCollider) { objects.push_back(raycastCollider); }

	virtual bool CheckCollision(const Ray& ray, double tMin, double tMax, RaycastHit& hitInfo) const override;

private:
	std::vector<shared_ptr<RaycastCollider>> objects;
};

bool Scene::CheckCollision(const Ray& ray, double tMin, double tMax, RaycastHit& hitInfo) const
{
	RaycastHit temp_rec;
	bool hitAnything = false;
	auto tClosest = tMax;

	for (const auto& object : objects)
	{
		if (object->CheckCollision(ray, tMin, tClosest, temp_rec))
		{
			hitAnything = true;
			tClosest = temp_rec.t;
		}
	}

	hitInfo = temp_rec;
	return hitAnything;
}