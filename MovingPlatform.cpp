#include "MovingPlatform.h"

MovingPlatform::MovingPlatform(Vector2 spawnPos, SDL_Color color, Vector2 colliderSize, Vector2 waypointOne, Vector2 waypointTwo, bool activate)
		: Entity(spawnPos, color, colliderSize, EntityType::MOVING_PLATFORM, activate)
{

}

void MovingPlatform::Update()
{

}