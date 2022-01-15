#pragma once

// this header contains abstract class that manages all hittables

#include "RaycastCollider.h"
#include "Utils.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class Scene : public RaycastCollider
{
public:
	Scene();
	Scene(shared_ptr<RaycastCollider> raycastCollider);

	void Clear();
	void AddCollider(shared_ptr<RaycastCollider> raycastCollider);

	virtual bool CheckCollision(const Ray& ray, double tMin, double tMax, RaycastHit& hitInfo) const override;

private:
	std::vector<shared_ptr<RaycastCollider>> objects;
};