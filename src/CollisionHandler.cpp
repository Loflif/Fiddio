#include "CollisionHandler.h"
#include "Entity.h"
#include <algorithm>

std::set<std::pair<EntityType, EntityType>> collisionPairs;

namespace CollisionHandler
{
	std::vector<Collision> collisions;

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

	bool RayIntersectsAABB(const Vector2 start, const Vector2 dir, const AABB aabb, HitInfo& hitInfo)
	{
		Vector2 nearHit
		{
			(aabb.min.x - start.x) / dir.x,
			(aabb.min.y - start.y) / dir.y 
		};

		Vector2 farHit
		{
			(aabb.min.x + aabb.dim.x - start.x) / dir.x,
			(aabb.min.y + aabb.dim.y - start.y) / dir.y 
		};

		auto swapIf = [](float& a, float& b)
		{
			if (a > b)
			{
				float temp = a;
				a = b;
				b = temp;
			}
		};
		swapIf(nearHit.x, farHit.x);
		swapIf(nearHit.y, farHit.y);

		// ray never intersects
		if (nearHit.x > farHit.y ||
			nearHit.y > farHit.x) return false;

		float t1 = std::max(nearHit.x, nearHit.y);
		float t2 = std::min(farHit.x, farHit.y);

		//intersection is behind us
		if (t1 < 0) return false;

		// If we got here, the hit happened.

		// Calculate the hit point
		hitInfo.point.x = start.x + (dir.x * t1);
		hitInfo.point.y = start.y + (dir.y * t1);

		// And the normal
		if (nearHit.x > nearHit.y)
		{
			// We hit in X
			if (dir.x < 0)
				hitInfo.normal = { 1, 0 };
			else
				hitInfo.normal = { -1, 0 };
		}
		else
		{
			// We hit in Y
			if (dir.y < 0)
				hitInfo.normal = { 0, 1 };
			else
				hitInfo.normal = { 0, -1 };
		}

		hitInfo.t = t1;

		return true;
	}

	bool SweptAABBtoAABB(const AABB a, const AABB b, Vector2 relDisplacement, HitInfo& hitInfo)
	{
		// early-out if nothing is moving.
		if (relDisplacement.x == 0 && relDisplacement.y == 0) return false;

		AABB minkowski
		{
			b.min.x - a.dim.x * 0.5f,
			b.min.y - a.dim.y * 0.5f,
			a.dim.x + b.dim.x,
			a.dim.y + b.dim.y 
		};
		Vector2 aCenter
		{
			a.min.x + a.dim.x * 0.5f,
			a.min.y + a.dim.y * 0.5f 
		};

		return (RayIntersectsAABB(aCenter, relDisplacement, minkowski, hitInfo) && hitInfo.t < 1);
	}

	CollisionDirection CheckAABB(Entity* a, Entity* b, float& t)
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

		Vector2 aMin = a->Position;
		Vector2 aMax = a->Position + a->ColliderSize;
		aMax.y *= -1; // y is flipped in SDL
		Vector2 bMin = b->Position;
		Vector2 bMax = b->Position + b->ColliderSize;
		bMax.y *= -1; // y is flipped in SDL

		for (int i = 0; i < 2; i++)
		{
			if (relativeVelocity.v[i] < 0.0f)
			{
				if (bMax.v[i] < aMin.v[i]) return CollisionDirection::NONE; // b is to the left of a and moving away
				if (aMax.v[i] < bMin.v[i]) tFirst = std::max((aMax.v[i] - bMin.v[i]) / relativeVelocity.v[i], tFirst);
				if (bMax.v[i] > aMin.v[i]) tLast = std::min((aMin.v[i] - bMax.v[i]) / relativeVelocity.v[i], tLast);
			}
			if (relativeVelocity.v[i] > 0.0f)
			{
				if (bMin.v[i] > aMax.v[i]) return CollisionDirection::NONE;
				if (bMax.v[i] < aMin.v[i]) tFirst = std::max((aMin.v[i] - bMax.v[i]) / relativeVelocity.v[i], tFirst);
				if (aMax.v[i] > bMin.v[i]) tLast = std::min((aMax.v[i] - bMin.v[i]) / relativeVelocity.v[i], tLast);
			}

			if (tFirst > tLast) return CollisionDirection::NONE;
		}

		t = tFirst;

		Vector2 aDelta = a->CurrentVelocity * (t * DELTA_TIME);
		Vector2 bDelta = b->CurrentVelocity * (t * DELTA_TIME);

		a->Position += aDelta;
		b->Position += bDelta;

		aMax = a->Position + aDelta + a->ColliderSize;
		bMax = b->Position + bDelta + b->ColliderSize;

		float epsilon = 0.0001f;

		CollisionDirection dir = CollisionDirection::NONE;

		if (std::fabsf(a->Position.x - bMax.x) < epsilon) dir = CollisionDirection::RIGHT;
		if (std::fabsf(b->Position.x - aMax.x) < epsilon) dir = CollisionDirection::LEFT;
		if (std::fabsf(a->Position.y - bMax.y) < epsilon) dir = CollisionDirection::DOWN;
		if (std::fabsf(b->Position.y - aMax.y) < epsilon) dir = CollisionDirection::UP; 

		return dir;
	}

	void CheckCollisions(std::vector<Entity*> dynamicEntities, std::vector<Entity*> staticEntities)
	{
		collisions.clear();

		for (int i = 0; i < dynamicEntities.size(); i++) // Check new Collisions
		{
			Entity* left = dynamicEntities[i];
			if (!left->IsActive)
				continue;

			for (int j = i + 1; j < dynamicEntities.size(); j++)
			{
				Entity* right = dynamicEntities[j];
				if (!right->IsActive)
					continue;

				if (!HasCollisionPair(std::pair<EntityType, EntityType>(left->T, right->T)))
					continue;

				HitInfo hitInfo;
				AABB a{ left->Position.x, left->Position.y, left->ColliderSize.x, left->ColliderSize.y };
				AABB b{ right->Position.x, right->Position.y, right->ColliderSize.x, right->ColliderSize.y };
				Vector2 relativeDisplacement = (left->CurrentVelocity - right->CurrentVelocity) * DELTA_TIME;

				if (SweptAABBtoAABB(a, b, relativeDisplacement, hitInfo))
				{
					collisions.push_back({ left, right, hitInfo });
				}
			}
			for (int j = 0; j < staticEntities.size(); j++)
			{
				Entity* right = staticEntities[j];
				if (!right->IsActive)
					continue;

				if (!HasCollisionPair(std::pair<EntityType, EntityType>(left->T, right->T)))
					continue;

				HitInfo hitInfo;
				AABB a{ left->Position.x, left->Position.y, left->ColliderSize.x, left->ColliderSize.y };
				AABB b{ right->Position.x, right->Position.y, right->ColliderSize.x, right->ColliderSize.y };
				Vector2 relativeDisplacement = (left->CurrentVelocity - right->CurrentVelocity) * DELTA_TIME;

				if (SweptAABBtoAABB(a, b, relativeDisplacement, hitInfo))
				{
					collisions.push_back({ left, right, hitInfo });
				}
			}
			if (collisions.size() > 0)
			{
				std::sort(collisions.begin(), collisions.end(),
					[](const Collision& a, Collision& b) -> bool
					{
						return a.hit.t < b.hit.t;
					});
				collisions[0].a->OnCollision(collisions[0].b, collisions[0].hit);
				collisions[0].b->OnCollision(collisions[0].a, collisions[0].hit);

				for (int i = 1; i < collisions.size(); i++)
				{
					Entity* left = collisions[i].a;
					Entity* right = collisions[i].b;

					AABB a{ left->Position.x, left->Position.y, left->ColliderSize.x, left->ColliderSize.y };
					AABB b{ right->Position.x, right->Position.y, right->ColliderSize.x, right->ColliderSize.y };

					Vector2 relativeDisplacement = (left->CurrentVelocity - right->CurrentVelocity) * DELTA_TIME;

					if (SweptAABBtoAABB(a, b, relativeDisplacement, collisions[i].hit))
					{
						collisions[i].a->OnCollision(collisions[i].b, collisions[i].hit);
						collisions[i].b->OnCollision(collisions[i].a, collisions[i].hit);
					}
				}
			}
		}
	}
}