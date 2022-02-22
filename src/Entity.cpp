#include "Entity.h"

uint64_t ENTITY_COUNT = 0;

Entity::Entity(Vector2 spawnPos, SDL_Color color, Vector2 colliderSize, EntityType type, bool activate)
	: Position(spawnPos),
	T(type),
	IsActive(activate),
	IsVisible(activate),
	Color(color),
	ColliderSize(colliderSize),
	ID(++ENTITY_COUNT) {}

Entity::~Entity()
{

}

void Entity::Render(SDL_Renderer* renderer, Vector2 cameraPos)
{
	if (!IsActive)
		return;

	SDL_Rect drawRect = { round(Position.x + cameraPos.x), round(Position.y + cameraPos.y), ColliderSize.x, ColliderSize.y };

	SDL_SetRenderDrawColor(renderer, Color.r, Color.g, Color.b, Color.a);
	SDL_RenderFillRect(renderer, &drawRect);
}

void Entity::Update()
{

}

void Entity::OnCollisionEnter(Entity* other, CollisionHandler::HitInfo hit)
{

}

void Entity::OnCollisionStay(Entity* other, CollisionHandler::HitInfo hit)
{

}

void Entity::OnCollisionExit(Entity* other, CollisionHandler::HitInfo oldHitInfo)
{

}

void Entity::Die()
{
	IsActive = false;
	IsVisible = false;
}
