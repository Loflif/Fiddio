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

	virtual void Render(SDL_Renderer* renderer, Vector2 cameraPos);
	virtual void Update();
	virtual void OnCollision(Entity* other, CollisionHandler::HitInfo hit);
	virtual void Die();
	
	Vector2 Position = Vector2(0, 0);
	Vector2 CurrentVelocity = Vector2(0, 0);
	Vector2 ColliderSize = Vector2(0, 0);

	EntityType T;
	bool IsActive = false;
	bool IsVisible = false;
protected:
	SDL_Color Color;
};