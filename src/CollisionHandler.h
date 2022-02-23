#pragma once
#include <vector>
#include "EntityType.h"
#include "Vector2.h"

class Entity;

extern const double DELTA_TIME;

namespace CollisionHandler
{
	struct HitInfo
	{
		Vector2 point;
		Vector2 normal;
		float t;
		Vector2 tXY;
	};

	struct AABB
	{
		AABB(float minX, float minY, float dimX, float dimY)
		{
			min = Vector2(minX, minY);
			dim = Vector2(dimX, dimY);
		};

		Vector2 min;
		Vector2 dim;
	};

	struct Collision
	{
		Entity* a;
		Entity* b;
		HitInfo hit;
	};

	void AddCollisionPair(std::pair<EntityType, EntityType> pair);
	bool HasCollisionPair(std::pair<EntityType, EntityType> collisionPair);
	bool SweptAABBtoAABB(const AABB a, const AABB b, Vector2 relDisplacement, HitInfo& hitInfo);
	bool MovingAABBtoAABB(AABB a, AABB b, Vector2 relDisplacement, HitInfo& hitInfo);
	bool RayIntersectsAABB(const Vector2 start, const Vector2 dir, const AABB aabb, HitInfo& hitInfo);
	void CheckCollisions(std::vector<Entity*> dynamicEntities, std::vector<Entity*> staticEntities);
	void Depenetrate(Collision collision);
	void CallOnEnter(Collision collision);
	void CallOnStay(Collision collision);
	void CallOnExit(Collision collision);
}