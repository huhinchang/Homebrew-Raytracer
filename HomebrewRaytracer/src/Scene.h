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

	virtual bool CheckCollision(const Ray& r, double t_min, double t_max, RaycastHit& rec) const override;

public:
	std::vector<shared_ptr<RaycastCollider>> objects;
};

bool Scene::CheckCollision(const Ray& r, double t_min, double t_max, RaycastHit& rec) const
{
	RaycastHit temp_rec;
	bool hitAnything = false;
	auto tClosest = t_max;

	for (const auto& object : objects)
	{
		if (object->CheckCollision(r, t_min, tClosest, temp_rec))
		{
			hitAnything = true;
			tClosest = temp_rec.t;
		}
	}

	rec = temp_rec;
	return hitAnything;
}