#pragma once
#include "Entity.h"

struct lua_State;

class Player : public Entity
{
public:
    Player(Vector2 spawnPos, SDL_Color color, Vector2 colliderSize, bool activate = true);
    virtual void Update() override;
    virtual void Render(SDL_Renderer* renderer, Vector2 cameraPos) override;
    virtual void OnCollisionEnter(Entity* other, CollisionHandler::HitInfo hit) override;
    virtual void OnCollisionStay(Entity* other, CollisionHandler::HitInfo hit) override;
    virtual void OnCollisionExit(Entity* other, CollisionHandler::HitInfo oldHitInfo) override;
    void SetPosition(Vector2 newPosition);
    void SetVelocity(Vector2 newVelocity);
    void SetVelocityX(float x);
    void SetVelocityY(float y);
private:
    void SpawnSmoke();
    void UpdateActiveSmoke();

	bool IsOnGround = true;
    float JumpHeldTimer = 0.0f;
    float SmokeSpawnThreshold = 32.0f;
    float SmokeDuration = 0.3f;
    float DistanceSinceLastSmokeSpawn = 0.0f;
    float SmokeMaxSize = 20.0f;
	const char* ScriptFile = "src/Player.lua";

    struct SmokeParticle
    {
        SDL_Rect DrawRect;
        float TimeActive = 0.0f;
        float Scale = 0.0f;
        Vector2 Acceleration = Vector2(0, -640);
        Vector2 Position = Vector2(0, 0);
        Vector2 CurrentVelocity = Vector2(0, 0);
        bool IsActive = false;
    };
    const static int SMOKE_COUNT = 10;
    SmokeParticle RunningSmokeParticles[SMOKE_COUNT];
    SDL_Color SmokeColor{ 200, 200, 200, 255 };
	int SmokeIterator = 0;
};

static int lua_SetPosition(lua_State* L);
static int lua_SetVelocity(lua_State* L);
static int lua_SetVelocityX(lua_State* L);
static int lua_SetVelocityY(lua_State* L);
