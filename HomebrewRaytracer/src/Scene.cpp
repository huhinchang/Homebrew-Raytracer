#include "Scene.h"

Scene::Scene() {}
Scene::Scene(shared_ptr<RaycastCollider> raycastCollider) { AddCollider(raycastCollider); }

void Scene::Clear() { objects.clear(); }
void Scene::AddCollider(shared_ptr<RaycastCollider> raycastCollider) { objects.push_back(raycastCollider); }

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