#pragma once
#include <set>
#include <vector>
#include "Entity.h"

class Entity;

extern std::set<std::pair<Entity::Type, Entity::Type>> collisionPairs;


namespace CollisionHandler
{
	void AddCollisionPair(std::pair<Entity::Type, Entity::Type> pair);
	bool HasCollisionPair(std::pair<Entity::Type, Entity::Type> collisionPair);
	bool AABB(Entity* left, Entity* right);
	void CheckCollisions(std::vector<Entity*> entities);
}