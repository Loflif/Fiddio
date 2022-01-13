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
	Position += CurrentVelocity * DELTA_TIME;

	int movementInput = 0;

	if (KeyDown(Key::A) || KeyDown(Key::Left))
		movementInput = -1;

	if (KeyDown(Key::D) || KeyDown(Key::Right))
		movementInput = 1;

	ScriptHandler::CallFunctionNoReturn(ScriptFile, "OnUpdate", this, DELTA_TIME, CurrentVelocity.x, CurrentVelocity.y, movementInput);

	if (IsOnGround &&
		(KeyPressed(Key::W) || KeyPressed(Key::Space)))
	{
		ScriptHandler::CallFunctionNoReturn(ScriptFile, "OnJump", this, DELTA_TIME, CurrentVelocity.y);
		IsOnGround = false;
	}
}


void Player::OnCollision(Entity* other, CollisionHandler::HitInfo hit)
{
	if (other->T == EntityType::WALL
		|| other->T == EntityType::PIPE
		|| other->T == EntityType::FLOATING_BLOCK
		|| other->T == EntityType::GROUND_BLOCK)
	{
		Vector2 recoilVelocity = CurrentVelocity.Dot(hit.normal) * hit.normal;
		CurrentVelocity -= recoilVelocity;
		if (hit.normal.y < 0)
		{
			IsOnGround = true;
		}
		else if (hit.normal.y > 0)
		{
			other->Die();
		}
	}
	if (other->T == EntityType::GOOMBA)
	{
		if (hit.normal.y < 0)
		{
			other->Die();
			ScriptHandler::CallFunctionNoReturn(ScriptFile, "OnBounce", this);
		}
		else
		{
			Die();
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
}

void Player::SetVelocityY(float y)
{
	CurrentVelocity.y = y;
}

int lua_SetPosition(lua_State* L)
{
	if (lua_gettop(L) != 3) return -1;
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
	return 0;
}

int lua_SetVelocityY(lua_State* L)
{
	if (lua_gettop(L) != 2) return -1;
	Player* player = static_cast<Player*>(lua_touserdata(L, 1));
	float y = lua_tonumber(L, 2);
	player->SetVelocityY(y);
	return 0;
}
