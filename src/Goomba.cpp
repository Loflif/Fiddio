#include "Goomba.h"
#include "ScriptHandler.h"

Goomba::Goomba(Vector2 spawnPos, SDL_Color color, Vector2 colliderSize, Vector2 waypointOne, Vector2 waypointTwo, bool activate)
	: Entity(spawnPos, color, colliderSize, EntityType::GOOMBA, activate)	
{
	MovementSpeed = ScriptHandler::GetTableFloat(ScriptFile, "Goomba", "MovementSpeed");
	
	CurrentWaypoint = waypointOne;
	OtherWaypoint = waypointTwo;
}

void Goomba::Update()
{
	if (MoveTowardsTarget(Position, CurrentWaypoint, MovementSpeed * DELTA_TIME))
		std::swap(CurrentWaypoint, OtherWaypoint);
}

void Goomba::OnCollision(Entity* other, CollisionHandler::HitInfo hit)
{
	
}

bool Goomba::MoveTowardsTarget(Vector2& position, const Vector2& target, const float step)
{
	Vector2 delta = target - position;
	
	float sqrDist = position.SqrDistanceTo(target);

	if (sqrDist < step * step)
	{
		position = target;
		return true;
	}

	Vector2 dir = delta.Normalize();
	CurrentVelocity = dir * (step / DELTA_TIME); // For collision purposes

	position += dir * step;

	return false;
}
