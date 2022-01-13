#pragma once
#include "Vector2.h"

#include <vector>

class Entity;
class Player;
struct lua_State;

extern std::vector<Entity*> STATIC_ENTITIES;
extern std::vector<Entity*> DYNAMIC_ENTITIES;
extern Player* PLAYER;

namespace LevelHandler
{
	void Init();
	void CleanUp();
	void LoadLevel(int w, int h, int tileSize);
	void SetTile(int x, int y, int type);
	void SpawnGoomba(int x, int y, int waypointOne, int waypointTwo);

	static int lua_LoadLevel(lua_State* L);
	static int lua_SetTile(lua_State* L);
	static int lua_SpawnGoomba(lua_State* L);
}