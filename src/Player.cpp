#include "Player.h"
#include "Fiddio.h"
#include "ScriptHandler.h"

Player::Player(Vector2 spawnPos, SDL_Color color, Vector2 colliderSize, bool activate)
	: Entity(spawnPos, color, colliderSize, EntityType::PLAYER, activate)
{
	ScriptHandler::RegisterFunction(ScriptFile, "_SetPosition", lua_SetPosition);
	ScriptHandler::RegisterFunction(ScriptFile, "_SetVelocity", lua_SetVelocity);
	ScriptHandler::RegisterFunction(ScriptFile, "_SetVelocityX", lua_SetVelocityX);
	ScriptHandler::RegisterFunction(ScriptFile, "_SetVelocityY", lua_SetVelocityY);
	ScriptHandler::CallFunctionNoReturn(ScriptFile, "OnStart", this);
}

void Player::Update()
{
	ScriptHandler::CallFunctionNoReturn(ScriptFile, "OnUpdate", this, DELTA_TIME);

	bool isFalling = CurrentVelocity.y < 0;
	ScriptHandler::CallFunctionNoReturn(ScriptFile, "AddGravity", this, DELTA_TIME, CurrentVelocity.y, isFalling);

	if (KeyPressed(Key::W) || KeyPressed(Key::Space))
		ScriptHandler::CallFunctionNoReturn(ScriptFile, "OnJump", this, DELTA_TIME, CurrentVelocity.y);

	if (KeyDown(Key::A) || KeyDown(Key::Left))
		ScriptHandler::CallFunctionNoReturn(ScriptFile, "OnAccelerateLeft", this, DELTA_TIME, CurrentVelocity.x);

	if (KeyDown(Key::D) || KeyDown(Key::Right))
		ScriptHandler::CallFunctionNoReturn(ScriptFile, "OnAccelerateRight", this, DELTA_TIME, CurrentVelocity.x);
		
	if(!KeyDown(Key::A) && !KeyDown(Key::Left) && !KeyDown(Key::D) && !KeyDown(Key::Right))
		ScriptHandler::CallFunctionNoReturn(ScriptFile, "OnDecelerate", this, DELTA_TIME, CurrentVelocity.x);

	Position += CurrentVelocity * DELTA_TIME;
}

void Player::OnCollision(Entity* other, CollisionHandler::CollisionDirection dir, float t)
{
	if (other->T == EntityType::WALL)
	{
		if (dir == CollisionHandler::CollisionDirection::INSIDE)
		{
			float distanceY = other->Position.y - Position.y;
			float penetrationY = (ColliderSize.y) - distanceY;

			Position.y -= penetrationY;

			/*float distanceX = std::abs(Position.x - other->Position.x);
			float penetrationX = (ColliderSize.x) - distanceX;

			Position.x += penetrationX;*/

			/*float distanceX = Position.x - other->Position.x;
			float penetrationX = distanceX - (other->ColliderSize.x / 2 + ColliderSize.x / 2);

			Position.x += penetrationX;*/

			CurrentVelocity.y = 0.0f;
		}
	}
}

void Player::SetPosition(Vector2 newPosition)
{
	Position = newPosition;
}

void Player::SetVelocity(Vector2 newVelocity)
{
	CurrentVelocity = newVelocity;
}

void Player::SetVelocityX(float x)
{
	CurrentVelocity.x = x;
	//printf("[C++]: SetVelocityX was called, new velocity is: %p\n", &CurrentVelocity.x);
}

void Player::SetVelocityY(float y)
{
	CurrentVelocity.y = y;
	//printf("[C++]: SetVelocityY was called, new velocity is: %p\n", &CurrentVelocity.y);
}

int lua_SetPosition(lua_State* L)
{
	if (lua_gettop(L) != 3) return -1;
	printf("I AM BEING  CLALED");
	Player* player = static_cast<Player*>(lua_touserdata(L, 1));
	float x = lua_tonumber(L, 2);
	float y = lua_tonumber(L, 3);
	player->SetPosition(Vector2(x, y));
	return 0;
}

int lua_SetVelocity(lua_State* L)
{
	if (lua_gettop(L) != 3) return -1;
	Player* player = static_cast<Player*>(lua_touserdata(L, 1));
	float x = lua_tonumber(L, 2);
	float y = lua_tonumber(L, 3);
	player->SetVelocity(Vector2(x, y));
	return 0;
}

int lua_SetVelocityX(lua_State* L)
{
	if (lua_gettop(L) != 2) return -1;
	Player* player = static_cast<Player*>(lua_touserdata(L, 1));
	float x = lua_tonumber(L, 2);
	player->SetVelocityX(x);
	//printf("[C++]: lua_SetVelocityX was called, new velocity is: %p\n", &x);
	return 0;
}

int lua_SetVelocityY(lua_State* L)
{
	if (lua_gettop(L) != 2) return -1;
	Player* player = static_cast<Player*>(lua_touserdata(L, 1));
	float y = lua_tonumber(L, 2);
	player->SetVelocityY(y);
	//printf("[C++]: lua_SetVelocityY was called, new velocity is: %p\n", &y);
	return 0;
}
