#pragma once
#include "Vector2.h"

#include <vector>

class Entity;

extern std::vector<Entity*> CurrentEntities;
extern std::vector<Entity*> ActiveEntities;

namespace LevelHandler
{
	void Init();
	void CleanUp();
	void LoadLevel(int w, int h, int tileSize);
	void SetTile(int x, int y, int type);
}