#pragma once
#include "SDL/SDL.h"
#include "Vector2.h"
#include <memory>

class Entity
{
public:
	enum class Type
	{
		EMPTY = 0,
		WALL = 1,
		PLAYER = 2,
		ENEMY = 3,
		PIPE = 4,
		
	};


	Entity() = delete;
	Entity(Vector2 spawnPos, SDL_Color color, Vector2 colliderSize, Type type, bool activate = true);

	~Entity();

	virtual void Render(SDL_Renderer* renderer);
	virtual void Update(double deltaTime);
	virtual void OnCollision(Entity* other);
	
	Vector2 Position = Vector2(0, 0);
	Vector2 ColliderSize = Vector2(0, 0);

	Type T;
	bool IsActive = false;
protected:
	SDL_Color Color;
};