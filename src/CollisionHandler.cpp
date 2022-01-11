#include "CollisionHandler.h"
#include "Vector2.h"
#include "Entity.h"
#include <algorithm>

std::set<std::pair<EntityType, EntityType>> collisionPairs;

namespace CollisionHandler
{
	void AddCollisionPair(std::pair<EntityType, EntityType> pair)
	{
		collisionPairs.insert(pair);
	}

	bool HasCollisionPair(std::pair<EntityType, EntityType> collisionPair)
	{
		std::pair<EntityType, EntityType> otherPair(collisionPair.second, collisionPair.first);
		if ((collisionPairs.find(collisionPair) != collisionPairs.end())
			|| collisionPairs.find(otherPair) != collisionPairs.end()) // Checks if set contains the pair or the pair in the other order
			return true;

		return false;
	}

	CollisionDirection AABB(Entity* a, Entity* b, float& t)
	{
		if (a->Position.x < b->Position.x + b->ColliderSize.x &&
			a->Position.x + a->ColliderSize.x > b->Position.x &&
			a->Position.y < b->Position.y + b->ColliderSize.y &&
			a->Position.y + a->ColliderSize.y > b->Position.y)
		{
			return CollisionDirection::INSIDE;
		}

		Vector2 relativeVelocity = (b->CurrentVelocity - a->CurrentVelocity) * DELTA_TIME;

		float tFirst = 0.0f;
		float tLast = 1.0f;

		Vector2 aBounds = a->Position + a->ColliderSize;
		aBounds.y *= -1;
		Vector2 bBounds = b->Position + b->ColliderSize;
		bBounds.y *= -1;

		for (int i = 0; i < 2; i++)
		{
			if (relativeVelocity.v[i] < 0.0f)
			{
				if (bBounds.v[i] < a->Position.v[i]) return CollisionDirection::NONE; // b is to the left of a and moving away
				if (aBounds.v[i] < b->Position.v[i]) tFirst = std::max((aBounds.v[i] - b->Position.v[i]) / relativeVelocity.v[i], tFirst);
				if (bBounds.v[i] > a->Position.v[i]) tLast = std::min((a->Position.v[i] - bBounds.v[i]) / relativeVelocity.v[i], tLast);
			}
			if (relativeVelocity.v[i] > 0.0f)
			{
				if (b->Position.v[i] > aBounds.v[i]) return CollisionDirection::NONE;
				if (bBounds.v[i] < a->Position.v[i]) tFirst = std::max((a->Position.v[i] - bBounds.v[i]) / relativeVelocity.v[i], tFirst);
				if (aBounds.v[i] > b->Position.v[i]) tLast = std::min((aBounds.v[i] - b->Position.v[i]) / relativeVelocity.v[i], tLast);
			}

			if (tFirst > tLast) return CollisionDirection::NONE;
		}

		t = tFirst;

		Vector2 aDelta = a->CurrentVelocity * (t * DELTA_TIME);
		Vector2 bDelta = b->CurrentVelocity * (t * DELTA_TIME);

		//printf("aDelta: %f,%f, bDelta: %f,%f\n", aDelta.x, aDelta.y, bDelta.x, bDelta.y);

		/*aDelta.y *= -1;
		bDelta.y *= -1;*/

		a->Position += aDelta;
		b->Position += bDelta;

		aBounds = a->Position + aDelta + a->ColliderSize;
		aBounds.y *= -1;
		bBounds = b->Position + bDelta + b->ColliderSize;
		bBounds.y *= -1;

		float epsilon = 0.01f;

		CollisionDirection dir = CollisionDirection::NONE;

		if (std::fabsf(a->Position.x - bBounds.x) < epsilon) dir = CollisionDirection::RIGHT;
		if (std::fabsf(b->Position.x - aBounds.x) < epsilon) dir = CollisionDirection::LEFT;
		if (std::fabsf(a->Position.y - bBounds.y) < epsilon) 
		{
			dir = CollisionDirection::DOWN;
		}
		if (std::fabsf(b->Position.y - aBounds.y) < epsilon) 
		{
			dir = CollisionDirection::UP;
		} 

		/*a->Position -= a->CurrentVelocity * TARGET_FRAME_SECONDS * (t);
		b->Position -= b->CurrentVelocity * TARGET_FRAME_SECONDS * (t);*/

		return dir;
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

				if (!HasCollisionPair(std::pair<EntityType, EntityType>(left->T, right->T)))
					continue;

				float t;
				CollisionDirection dir = AABB(left, right, t);


				if (dir != CollisionDirection::NONE)
				{
					//printf("%i\n", dir);

					left->OnCollision(right, dir, t);
					right->OnCollision(left, dir, t);
				}
			}
		}
	}
}