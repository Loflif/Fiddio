#include "Goomba.h"
#include "ScriptHandler.h"

Goomba::Goomba(Vector2 spawnPos, SDL_Color color, Vector2 colliderSize, float waypointOne, float waypointTwo, int id, bool activate)
	: Entity(spawnPos, color, colliderSize, EntityType::GOOMBA, activate)	
{
	ID = id;

	ScriptHandler::RegisterFunction(ScriptFile, "_SetPosition", lua_SetPosition);
	ScriptHandler::RegisterFunction(ScriptFile, "_SetVelocity", lua_SetVelocity);

	ScriptHandler::CallFunctionNoReturn(ScriptFile, "OnStart", this, spawnPos.x, spawnPos.y, waypointOne, waypointTwo, id);
}

void Goomba::Update()
{
	ScriptHandler::CallFunctionNoReturn(ScriptFile, "OnUpdate", this, DELTA_TIME, Position.x, Position.y, ID);
	//Position += CurrentVelocity * DELTA_TIME;

	//ScriptHandler::CallFunctionNoReturn(ScriptFile, "OnUpdate", this, DELTA_TIME, CurrentVelocity.x);
}

void Goomba::OnCollision(Entity* other, CollisionHandler::HitInfo hit)
{
	if (other->T == EntityType::WALL
		|| other->T == EntityType::PIPE
		|| other->T == EntityType::GROUND_BLOCK
		|| other->T == EntityType::FLOATING_BLOCK)
	{
		//CurrentVelocity.x *= -1;
	}
}

void Goomba::SetPosition(Vector2 newPosition)
{
	Position = newPosition;
}

void Goomba::SetVelocity(Vector2 newVelocity)
{
	CurrentVelocity = newVelocity;
}

int lua_SetPosition(lua_State* L)
{
	if (lua_gettop(L) != 3) return -1;
	Goomba* goomba = static_cast<Goomba*>(lua_touserdata(L, 1));
	float x = lua_tonumber(L, 2);
	float y = lua_tonumber(L, 3);
	goomba->SetPosition(Vector2(x, y));
	return 0;
}

int lua_SetVelocity(lua_State* L)
{
	if (lua_gettop(L) != 3) return -1;
	Goomba* goomba = static_cast<Goomba*>(lua_touserdata(L, 1));
	float x = lua_tonumber(L, 2);
	float y = lua_tonumber(L, 3);
	goomba->SetVelocity(Vector2(x, y));
	return 0;
}