#include "LevelHandler.h"

#include "ScriptHandler.h"
#include "Entity.h"
#include "Player.h"
#include "Fiddio.h"

std::vector<Entity*> CurrentEntities;
std::vector<Entity*> ActiveEntities;

namespace LevelHandler
{
	void Init()
	{
		ScriptHandler::CallFunctionNoReturn("src/LevelLoader.lua", "LoadLevel", 1);
	}

	void CleanUp()
	{
		for (auto entity : CurrentEntities)
		{
			delete entity;
		}
	}

	Vector2 LevelOneSize = Vector2(0, 0);

	SDL_Color playerColor = SDL_Color{ 173, 70, 62, 1 };
	SDL_Color wallColor = SDL_Color{ 214, 105, 56, 1 };
	SDL_Color pipeColor = SDL_Color{ 1, 168, 0, 1 };

	int TileSize;

	void LoadLevel(int w, int h, int tileSize)
	{
		LevelOneSize = { (float)w, (float)h };
		TileSize = tileSize;
	}

	void SetTile(int x, int y, int type)
	{
		Vector2 tilePosition = Vector2(x * TileSize, y * TileSize);

		Entity::Type t = (Entity::Type)type;

		switch (t)
		{
			case Entity::Type::EMPTY:
			{
				break;
			}
			case Entity::Type::WALL:
			{
				Entity* wall = new Entity(tilePosition, wallColor, Vector2(TileSize, TileSize), Entity::Type::WALL, true);
				CurrentEntities.push_back(wall);
				break;
			}
			case Entity::Type::PLAYER:
			{
				Player* player = new Player(tilePosition, playerColor, Vector2(TileSize, TileSize), true);
				CurrentEntities.push_back(player);
				ActiveEntities.push_back(player);
				break;
			}
			case Entity::Type::ENEMY:
			{
				break;
			}
			case Entity::Type::PIPE:
			{
				Entity* pipe = new Entity(tilePosition, pipeColor, Vector2(TileSize, TileSize), Entity::Type::PIPE, true);
				CurrentEntities.push_back(pipe);
				break;
			}

			default:
			{
				break;
			}
		}
	}
}
