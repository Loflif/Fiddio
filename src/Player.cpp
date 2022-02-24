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

	UpdateActiveSmoke();
	if (IsOnGround)
		DistanceSinceLastSmokeSpawn += CurrentVelocity.x * DELTA_TIME;

	if(DistanceSinceLastSmokeSpawn >= SmokeSpawnThreshold)
	{
		SpawnSmoke();
		DistanceSinceLastSmokeSpawn -= SmokeSpawnThreshold;
	}

	//printf("x: %f, y: %f\n", Position.x, Position.y);

	int movementInput = 0;

	if (KeyDown(Key::A) || KeyDown(Key::Left))
		movementInput = -1;

	if (KeyDown(Key::D) || KeyDown(Key::Right))
		movementInput = 1;

	//printf("Calling OnUpdate with %f as velocity\n", CurrentVelocity.y);
	ScriptHandler::CallFunctionNoReturn(ScriptFile, "OnUpdate", 
		this, DELTA_TIME, CurrentVelocity.x, CurrentVelocity.y, movementInput);

	if (KeyPressed(Key::W) || KeyPressed(Key::Space))
	{
		if(IsOnGround)
		{
			Jump();
		}
		else
		{
			JumpGraceTimer = 0;
		}
	}

	if(KeyDown(Key::W) || KeyDown(Key::Space))
	{
		ScriptHandler::CallFunctionNoReturn(ScriptFile, "OnJumpHeld", this, CurrentVelocity.y, DELTA_TIME, JumpHeldTimer);
	}

	JumpHeldTimer += DELTA_TIME;
	if(JumpGraceTimer < JumpGraceDuration)
	{
		JumpGraceTimer += DELTA_TIME;

		if (!IsJumping && IsOnGround)
		{
			Jump();
		}
	}

	if(CurrentPlatform != nullptr)
	{
		Position += CurrentPlatform->CurrentVelocity * DELTA_TIME;
	}
}

void Player::Render(SDL_Renderer* renderer, Vector2 cameraPos)
{
	Entity::Render(renderer, cameraPos);

	for(auto& rect : RunningSmokeParticles)
	{
		if (!rect.IsActive)
			continue;

		SDL_Rect drawRect = 
		{
			round(rect.Position.x + cameraPos.x + rect.Scale * 0.5f),
			round(rect.Position.y + cameraPos.y - rect.Scale * 0.5f),
			round(rect.Scale),
			round(rect.Scale)
		};

		SDL_SetRenderDrawColor(renderer, SmokeColor.r, SmokeColor.g, SmokeColor.b, SmokeColor.a);
		SDL_RenderFillRect(renderer, &drawRect);
	}
}

void Player::OnCollisionEnter(Entity* other, CollisionHandler::HitInfo hit)
{
	//printf("Player::OnCollisionEnter\n");
	if (other->T == EntityType::WALL
		|| other->T == EntityType::PIPE
		|| other->T == EntityType::FLOATING_BLOCK
		|| other->T == EntityType::GROUND_BLOCK)
	{
		if (hit.normal.y < 0)
		{
			IsOnGround = true;
			IsJumping = false;
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
	if(other->T == EntityType::MOVING_PLATFORM)
	{
		CurrentPlatform = other;
		if (hit.normal.y < 0)
		{
			IsOnGround = true;
			IsJumping = false;
		}
	}
}


void Player::OnCollisionStay(Entity* other, CollisionHandler::HitInfo hit)
{
	
}

void Player::OnCollisionExit(Entity* other, CollisionHandler::HitInfo oldHitInfo)
{
	if(other->T == EntityType::MOVING_PLATFORM)
	{
		CurrentPlatform = nullptr;
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

void Player::SpawnSmoke()
{
	SmokeIterator++;
	int i = SmokeIterator%SMOKE_COUNT;
	RunningSmokeParticles[i].IsActive = true;

	RunningSmokeParticles[i].Position = Vector2(Position.x, Position.y + ColliderSize.y);

	RunningSmokeParticles[i].Scale = 0;
	RunningSmokeParticles[i].CurrentVelocity = Vector2(0, 0);
	RunningSmokeParticles[i].DrawRect.w = RunningSmokeParticles[i].Scale;
	RunningSmokeParticles[i].DrawRect.h = RunningSmokeParticles[i].Scale;

	RunningSmokeParticles[i].TimeActive = 0.0f;
}

void Player::Jump()
{
	ScriptHandler::CallFunctionNoReturn(ScriptFile, "OnJump", this, CurrentVelocity.y);
	JumpHeldTimer = 0.0f;
	IsOnGround = false;
	IsJumping = true;
}

void Player::UpdateActiveSmoke()
{
	for (auto& rect : RunningSmokeParticles)
	{
		if (!rect.IsActive)
			continue;

		rect.TimeActive += DELTA_TIME;

		if (rect.TimeActive >= SmokeDuration)
		{
			rect.IsActive = false;
			continue;
		}

		rect.CurrentVelocity += rect.Acceleration * DELTA_TIME;
		rect.Position += rect.CurrentVelocity * DELTA_TIME;

		rect.Scale = sin((rect.TimeActive * 3.14) / SmokeDuration) * SmokeMaxSize;
	}
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
