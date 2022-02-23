#pragma once
#include "Entity.h"
class MovingPlatform :  public Entity
{
public:
	MovingPlatform(Vector2 spawnPos, SDL_Color color, Vector2 colliderSize, Vector2 waypointOne, Vector2 waypointTwo, bool activate = true);

	virtual void Update() override;

	
};