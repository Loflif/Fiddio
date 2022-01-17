#pragma once
#include "Entity.h"

struct lua_State;

class Goomba : public Entity
{
public:
	Goomba(Vector2 spawnPos, SDL_Color color, Vector2 colliderSize, Vector2 waypointOne, Vector2 waypointTwo, bool activate = true);
	virtual void Update() override;
	virtual void OnCollision(Entity* other, CollisionHandler::HitInfo hit) override;
private:
	bool MoveTowardsTarget(Vector2& position, const Vector2& target, const float step);
	
	const char* ScriptFile = "src/Goomba.lua";
	float MovementSpeed = 0.0f;
	Vector2 CurrentWaypoint = Vector2(0, 0);
	Vector2 OtherWaypoint = Vector2(0, 0);
};

