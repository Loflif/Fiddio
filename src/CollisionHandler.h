#pragma once
#include <set>
#include <vector>
#include "EntityType.h"

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

	void AddCollisionPair(std::pair<EntityType, EntityType> pair);
	bool HasCollisionPair(std::pair<EntityType, EntityType> collisionPair);
	CollisionDirection AABB(Entity* a, Entity* b, float& t);
	void CheckCollisions(std::vector<Entity*> entities);
}