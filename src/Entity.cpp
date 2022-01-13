#include "Entity.h"

Entity::Entity(Vector2 spawnPos, SDL_Color color, Vector2 colliderSize, EntityType type, bool activate)
	: Position(spawnPos),
	T(type),
	IsActive(activate),
	IsVisible(activate),
	Color(color),
	ColliderSize(colliderSize) {}

Entity::~Entity()
{

}

void Entity::Render(SDL_Renderer* renderer, Vector2 cameraPos)
{
	if (!IsActive)
		return;

	SDL_Rect drawRect = {round(Position.x + cameraPos.x), round(Position.y + cameraPos.y), ColliderSize.x, ColliderSize.y};

	SDL_SetRenderDrawColor(renderer, Color.r, Color.g, Color.b, Color.a);
	SDL_RenderFillRect(renderer, &drawRect);
}

void Entity::Update()
{

}

void Entity::OnCollision(Entity* other, CollisionHandler::HitInfo hit)
{

}

void Entity::Die()
{
	IsActive = false;
	IsVisible = false;
}
