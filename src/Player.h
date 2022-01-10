#pragma once
#include "Entity.h"

struct lua_State;

class Player : public Entity
{
public:
    Player(Vector2 spawnPos, SDL_Color color, Vector2 colliderSize, bool activate = true);
    virtual void Update(double deltaTime) override;
    virtual void OnCollision(Entity* other);
    void SetVelocity(Vector2 newVelocity);
    Vector2 GetVelocity();
private:
    void ChangeVelocity(double deltaTime);

    Vector2 CurrentVelocity = Vector2(0, 0);

    bool IsOnGround = true;

    const char* ScriptFile = "src/Player.lua";
};

static int lua_SetVelocity(lua_State* L);
static int lua_GetVelocity(lua_State* L);