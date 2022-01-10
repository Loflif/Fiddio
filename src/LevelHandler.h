#pragma once
#include "Vector2.h"

#include <vector>

class Entity;
struct lua_State;

extern std::vector<Entity*> CurrentEntities;
extern std::vector<Entity*> ActiveEntities;

namespace LevelHandler
{
	void Init();
	void CleanUp();
	void LoadLevel(int w, int h, int tileSize);
	void SetTile(int x, int y, int type);

	static int lua_LoadLevel(lua_State* L);
	static int lua_SetTile(lua_State* L);
}