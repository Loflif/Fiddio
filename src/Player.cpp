#include "Player.h"
#include "Fiddio.h"
#include "ScriptHandler.h"

Player::Player(Vector2 spawnPos, SDL_Color color, Vector2 colliderSize, bool activate)
	: Entity(spawnPos, color, colliderSize, Entity::Type::PLAYER, activate)
{
	ScriptHandler::RegisterFunction(ScriptFile, "_SetVelocity", lua_SetVelocity);
	ScriptHandler::CallFunctionNoReturn(ScriptFile, "OnStart", this);
}

void Player::Update(double deltaTime)
{
	ScriptHandler::CallFunctionNoReturn(ScriptFile, "OnUpdate", this, deltaTime);

	ChangeVelocity(deltaTime);

	if (KeyPressed(Key::W) || KeyPressed(Key::Space))
	{
		CurrentVelocity.y -= 200.0f;
		printf("BOING");
	}

	Position += CurrentVelocity * deltaTime;
}

void Player::OnCollision(Entity* other)
{
	if (other->T == Entity::Type::WALL)
	{
		float distance = other->Position.y - Position.y;
		float penetration = distance - (ColliderSize.y / 2 + other->ColliderSize.y / 2);

		Position.y += penetration;
		CurrentVelocity.y = 0;
	}
}

void Player::SetVelocity(Vector2 newVelocity)
{
	CurrentVelocity = newVelocity;
}

Vector2 Player::GetVelocity()
{
	return CurrentVelocity;
}

void Player::ChangeVelocity(double deltaTime) // Make into lua script
{
	const float MOVEMENT_SPEED = 500.0f;
	const float GRAVITY = 980.0f;

	int frameInputX = 0;

	if (KeyDown(Key::A) || KeyDown(Key::Left)) frameInputX -= 1;
	if (KeyDown(Key::D) || KeyDown(Key::Right))	frameInputX += 1;

	CurrentVelocity.x += frameInputX * (MOVEMENT_SPEED * deltaTime);
	CurrentVelocity.y += GRAVITY * deltaTime;
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

int lua_GetVelocity(lua_State* L)
{
	if (lua_gettop(L) != 1) return -1;
	Player* player = static_cast<Player*>(lua_touserdata(L, 1));

	return 0;
}
