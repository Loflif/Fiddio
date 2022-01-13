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
	void SetVelocity(Vector2 newVelocity);
private:
	const char* ScriptFile = "src/Goomba.lua";
	int ID = -1;
};

static int lua_SetPosition(lua_State* L);
static int lua_SetVelocity(lua_State* L);

