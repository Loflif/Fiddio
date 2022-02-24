#pragma once
#include "Entity.h"
class MovingPlatform :  public Entity
{
public:
	MovingPlatform(Vector2 spawnPos, SDL_Color color, Vector2 colliderSize, Vector2 waypointOne, Vector2 waypointTwo, float speed, bool activate = true);

	virtual void Update() override;
	bool MoveTowardsWaypoint(Vector2& position, const Vector2& target, const float step);

	const char* ScriptFile = "src/MovingPlatform.lua";
	float MovementSpeed = 0.0f;
	Vector2 CurrentWaypoint = Vector2(0, 0);
	Vector2 OtherWaypoint = Vector2(0, 0);
};