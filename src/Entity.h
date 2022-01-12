#pragma once
#include "SDL/SDL.h"
#include "Vector2.h"
#include <memory>
#include "CollisionHandler.h"
#include "EntityType.h"

extern const double DELTA_TIME;

class Entity
{
public:
	Entity() = delete;
	Entity(Vector2 spawnPos, SDL_Color color, Vector2 colliderSize, EntityType type, bool activate = true);

	~Entity();

	virtual void Render(SDL_Renderer* renderer);
	virtual void Update();
	virtual void OnCollision(Entity* other, CollisionHandler::HitInfo hit);
	//virtual void OnCollision(Entity* other, CollisionHandler::CollisionDirection dir, float t);
	
	Vector2 Position = Vector2(0, 0);
	Vector2 CurrentVelocity = Vector2(0, 0);
	Vector2 ColliderSize = Vector2(0, 0);

	EntityType T;
	bool IsActive = false;
protected:
	SDL_Color Color;
};