#include "LevelHandler.h"

#include "ScriptHandler.h"

#include "Entity.h"
#include "Player.h"
#include "Goomba.h"
#include "Fiddio.h"

std::vector<Entity*> STATIC_ENTITIES;
std::vector<Entity*> DYNAMIC_ENTITIES;
Player* PLAYER;

namespace LevelHandler
{
	void Init()
	{
		if (!ScriptHandler::RegisterFunction("src/LevelLoader.lua", "_LoadLevel", lua_LoadLevel))
		{
			std::cout << "LevelHandler.Init() could not register function lua_LoadLevel in scripthandler " << std::endl;
		}
		if (!ScriptHandler::RegisterFunction("src/LevelLoader.lua", "_SetTile", lua_SetTile))
		{
			std::cout << "LevelHandler.Init() could not register function lua_SetTile in scripthandler " << std::endl;
		}
		if (!ScriptHandler::RegisterFunction("src/LevelLoader.lua", "_SpawnGoomba", lua_SpawnGoomba))
		{
			std::cout << "LevelHandler.Init() could not register function lua_SpawnGoomba in scripthandler " << std::endl;
		}
		if (!ScriptHandler::CallFunctionNoReturn("src/LevelLoader.lua", "LoadLevel", 1))
		{
			std::cout << "LevelHandler.Init() could not call function LoadLevel in scripthandler " << std::endl;
		}
	}

	void CleanUp()
	{
		for (auto entity : STATIC_ENTITIES)
		{
			delete entity;
		}

		for (auto entity : DYNAMIC_ENTITIES)
		{
			delete entity;
		}
	}

	Vector2 LevelOneSize = Vector2(0, 0);

	SDL_Color playerColor = SDL_Color{ 248, 56, 0, 1 };
	SDL_Color goombaColor = SDL_Color{ 255, 204, 197, 1 };
	SDL_Color wallColor = SDL_Color{ 214, 105, 56, 1 };
	SDL_Color pipeColor = SDL_Color{ 1, 168, 0, 1 };
	SDL_Color groundBlockColor = SDL_Color{ 153, 78, 0, 1 };
	SDL_Color floatingBlockColor = SDL_Color{ 153, 78, 0, 1 };

	int TileSize;

	void LoadLevel(int w, int h, int tileSize)
	{
		LevelOneSize = { (float)w, (float)h };
		TileSize = tileSize;
	}

	void SetTile(int x, int y, int type)
	{
		Vector2 tilePosition = Vector2(x * TileSize, y * TileSize);

		EntityType t = (EntityType)type;

		switch (t)
		{
			case EntityType::EMPTY:
			{
				break;
			}
			case EntityType::WALL:
			{
				Entity* wall = new Entity(tilePosition, wallColor, Vector2(TileSize, TileSize), EntityType::WALL, true);
				STATIC_ENTITIES.push_back(wall);
				break;
			}
			case EntityType::PLAYER:
			{
				Player* player = new Player(tilePosition, playerColor, Vector2(TileSize, TileSize), true);
				PLAYER = player;
				DYNAMIC_ENTITIES.push_back(player);
				break;
			}
			case EntityType::PIPE:
			{
				Entity* pipe = new Entity(tilePosition, pipeColor, Vector2(TileSize, TileSize), EntityType::PIPE, true);
				STATIC_ENTITIES.push_back(pipe);
				break;
			}
			case EntityType::FLOATING_BLOCK:
			{
				Entity* floatingBlock = new Entity(tilePosition, floatingBlockColor, Vector2(TileSize, TileSize), EntityType::FLOATING_BLOCK, true);
				STATIC_ENTITIES.push_back(floatingBlock);
				break;
			}
			case EntityType::GROUND_BLOCK:
			{
				Entity* groundBlock = new Entity(tilePosition, groundBlockColor, Vector2(TileSize, TileSize), EntityType::GROUND_BLOCK, true);
				STATIC_ENTITIES.push_back(groundBlock);
				break;
			}

			default:
			{
				break;
			}
		}
	}

	void SpawnGoomba(int x, int y, int waypointOneX, int waypointTwoX)
	{
		Vector2 goombaPosition = Vector2(x * TileSize, y * TileSize);
		Vector2 waypointOne = Vector2(waypointOneX * TileSize, goombaPosition.y);
		Vector2 waypointTwo = Vector2(waypointTwoX * TileSize, goombaPosition.y);
		Goomba* goomba = new Goomba(goombaPosition, goombaColor, Vector2(TileSize, TileSize), waypointOne, waypointTwo, true);
		DYNAMIC_ENTITIES.push_back(goomba);
	}

	static int lua_LoadLevel(lua_State* L)
	{
		if (lua_gettop(L) != 3) return -1;
		int w = lua_tointeger(L, 1);
		int h = lua_tointeger(L, 2);
		int tileSize = lua_tointeger(L, 3);
		LoadLevel(w, h, tileSize);
		return 0;
	}

	static int lua_SetTile(lua_State* L)
	{
		if (lua_gettop(L) != 3) return -1;
		int x = lua_tointeger(L, 1);
		int y = lua_tointeger(L, 2);
		int type = lua_tointeger(L, 3);
		SetTile(x - 1, y - 1, type);
		return 0;
	}
	int lua_SpawnGoomba(lua_State* L)
	{
		if (lua_gettop(L) != 4) return -1;
		int x = lua_tointeger(L, 1);
		int y = lua_tointeger(L, 2);
		int waypointOneX = lua_tointeger(L, 3);
		int waypointTwoX = lua_tointeger(L, 4);
		SpawnGoomba(x - 1, y - 1, waypointOneX - 1, waypointTwoX - 1);
		return 0;
	}
}
