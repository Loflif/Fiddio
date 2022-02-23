#pragma once
#include "SDL/SDL.h"
#include "Vector2.h"
#include "LuaIncludes.h"

class DustParticle
{
public:
	DustParticle();
	void Update();
	void Render(SDL_Renderer* renderer, Vector2 cameraPos);

	void SetScale(float scale);
	void Spawn(Vector2 position);
private:
	float TimeActive = 0.0f;
	float Scale = 0.0f;
	bool IsActive = false;

	const char* ScriptFile = "src/DustParticle.lua";
	SDL_Color SmokeColor{ 200, 200, 200, 255 };
	SDL_Rect DrawRect;
};

static int lua_SetScale(lua_State* L);
static int lua_SetPosition(lua_State* L);
static int lua_SetVelocityY(lua_State* L);