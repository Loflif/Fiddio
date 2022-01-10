#include "CollisionHandler.h"

std::set<std::pair<Entity::Type, Entity::Type>> collisionPairs;

namespace CollisionHandler
{
	void AddCollisionPair(std::pair<Entity::Type, Entity::Type> pair)
	{
		collisionPairs.insert(pair);
	}

	bool HasCollisionPair(std::pair<Entity::Type, Entity::Type> collisionPair)
	{
		std::pair<Entity::Type, Entity::Type> otherPair(collisionPair.second, collisionPair.first);
		if ((collisionPairs.find(collisionPair) != collisionPairs.end())
			|| collisionPairs.find(otherPair) != collisionPairs.end()) // Checks if set contains the pair or the pair in the other order
			return false;

		return true;
	}

	bool AABB(Entity* left, Entity* right)
	{
		if (left->Position.x < right->Position.x + right->ColliderSize.x &&
			left->Position.x + left->ColliderSize.x > right->Position.x &&
			left->Position.y < right->Position.y + right->ColliderSize.y &&
			left->Position.y + left->ColliderSize.y > right->Position.y)
		{
			return true;
		}
		return false;
	}

	void CheckCollisions(std::vector<Entity*> entities)
	{
		for (int i = 0; i < entities.size(); i++) // Check new Collisions
		{
			Entity* left = entities[i];
			if (!left->IsActive)
				continue;

			for (int j = i + 1; j < entities.size(); j++)
			{
				Entity* right = entities[j];
				if (!right->IsActive)
					continue;

				if (!HasCollisionPair(std::pair<Entity::Type, Entity::Type>(left->T, right->T)))
					continue;

				if (AABB(left, right))
				{
					left->OnCollision(right);
					right->OnCollision(left);
				}
			}
		}
	}
}