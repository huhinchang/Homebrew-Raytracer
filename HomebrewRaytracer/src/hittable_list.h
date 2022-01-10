#pragma once

// this header contains abstract class that manages all hittables

#include "RaycastCollider.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hittable_list : public RaycastCollider
{
public:
	hittable_list() {}
	hittable_list(shared_ptr<RaycastCollider> object) { add(object); }

	void clear() { objects.clear(); }
	void add(shared_ptr<RaycastCollider> object) { objects.push_back(object); }

	virtual bool CheckCollision(
		const Ray& r, double t_min, double t_max, RaycastHit& rec) const override;

public:
	std::vector<shared_ptr<RaycastCollider>> objects;
};

bool hittable_list::CheckCollision(const Ray& r, double t_min, double t_max, RaycastHit& rec) const
{
	RaycastHit temp_rec;
	bool hit_anything = false;
	auto closest_so_far = t_max;

	for (const auto& object : objects)
	{
		if (object->CheckCollision(r, t_min, closest_so_far, temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}

	return hit_anything;
}