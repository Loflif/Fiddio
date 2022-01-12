#pragma once
#include "Entity.h"

struct lua_State;

class Player : public Entity
{
public:
    Player(Vector2 spawnPos, SDL_Color color, Vector2 colliderSize, bool activate = true);
    virtual void Update() override;
    virtual void OnCollision(Entity* other, CollisionHandler::HitInfo hit) override;
    void SetPosition(Vector2 newPosition);
    void SetVelocity(Vector2 newVelocity);
    void SetVelocityX(float x);
    void SetVelocityY(float y);
private:
    bool IsOnGround = true;
    const char* ScriptFile = "src/Player.lua";
};

static int lua_SetPosition(lua_State* L);
static int lua_SetVelocity(lua_State* L);
static int lua_SetVelocityX(lua_State* L);
static int lua_SetVelocityY(lua_State* L);
