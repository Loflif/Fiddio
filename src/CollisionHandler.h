#pragma once
#include <set>
#include <vector>
#include "EntityType.h"
#include "Vector2.h"

class Entity;

extern const double DELTA_TIME;

namespace CollisionHandler
{
	enum class CollisionDirection
	{
		NONE,
		UP,
		RIGHT,
		DOWN,
		LEFT,
		INSIDE
	};

	struct HitInfo
	{
		Vector2 point;
		Vector2 normal;
		float t;
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
	bool RayIntersectsAABB(const Vector2 start, const Vector2 dir, const AABB aabb, HitInfo& hitInfo);
	CollisionDirection CheckAABB(Entity* a, Entity* b, float& t);
	void CheckCollisions(std::vector<Entity*> dynamicEntities, std::vector<Entity*> staticEntities);
}