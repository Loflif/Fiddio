#pragma once
#include "Entity.h"

struct lua_State;

class Goomba : public Entity
{
public:
	Goomba(Vector2 spawnPos, SDL_Color color, Vector2 colliderSize, float waypointOne, float waypointTwo, int id, bool activate = true);
	virtual void Update() override;
	virtual void OnCollision(Entity* other, CollisionHandler::HitInfo hit) override;
	void SetPosition(Vector2 newPosition);
	void SetPositionX(float newX);
	void SetVelocity(Vector2 newVelocity);
	void SetVelocityX(float newX);
private:
	const char* ScriptFile = "src/Goomba.lua";
	int ID = -1;
};

static int lua_SetPosition(lua_State* L);
static int lua_SetPositionX(lua_State* L);
static int lua_SetVelocity(lua_State* L);
static int lua_SetVelocityX(lua_State* L)

