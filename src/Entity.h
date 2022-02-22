#pragma once
#include "SDL/SDL.h"
#include "Vector2.h"
#include "CollisionHandler.h"
#include "EntityType.h"

extern const double DELTA_TIME;
extern uint64_t ENTITY_COUNT;

class Entity
{
public:
	Entity() = delete;
	Entity(Vector2 spawnPos, SDL_Color color, Vector2 colliderSize, EntityType type, bool activate = true);

	~Entity();

	virtual void Render(SDL_Renderer* renderer, Vector2 cameraPos);
	virtual void Update();
	virtual void OnCollisionEnter(Entity* other, CollisionHandler::HitInfo hit);
	virtual void OnCollisionStay(Entity* other, CollisionHandler::HitInfo hit);
	virtual void OnCollisionExit(Entity* other, CollisionHandler::HitInfo oldHitInfo);
	virtual void Die();
	
	Vector2 Position = Vector2(0, 0);
	Vector2 CurrentVelocity = Vector2(0, 0);
	Vector2 ColliderSize = Vector2(0, 0);

	EntityType T;
	bool IsActive = false;
	bool IsVisible = false;

	uint64_t ID;
protected:
	SDL_Color Color;
};