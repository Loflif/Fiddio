#include "MovingPlatform.h"

MovingPlatform::MovingPlatform(Vector2 spawnPos, SDL_Color color, Vector2 colliderSize, Vector2 waypointOne, Vector2 waypointTwo, float speed, bool activate)
		: Entity(spawnPos, color, colliderSize, EntityType::MOVING_PLATFORM, activate)
{
	MovementSpeed = speed;

	CurrentWaypoint = waypointOne;
	OtherWaypoint = waypointTwo;
}

void MovingPlatform::Update()
{
	if (MoveTowardsWaypoint(Position, CurrentWaypoint, MovementSpeed * DELTA_TIME))
		std::swap(CurrentWaypoint, OtherWaypoint);
}

bool MovingPlatform::MoveTowardsWaypoint(Vector2& position, const Vector2& target, const float step)
{
	Vector2 delta = target - position;

	float sqrDist = position.SqrDistanceTo(target);

	if (sqrDist < step * step)
	{
		position = target;
		return true;
	}

	Vector2 dir = delta.Normalize();
	CurrentVelocity = dir * (step / DELTA_TIME);

	position += dir * step;

	return false;
}