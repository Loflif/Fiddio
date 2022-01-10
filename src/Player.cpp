#include "Player.h"
#include "Fiddio.h"

Player::Player(Vector2 spawnPos, SDL_Color color, Vector2 colliderSize, bool activate)
	: Entity(spawnPos, color, colliderSize, Entity::Type::PLAYER, activate)
{
	
}

void Player::Update(double deltaTime)
{
	ChangeVelocity(deltaTime);
	Position += CurrentVelocity * deltaTime;

	LastPosition = Position;
}

void Player::OnCollision(Entity* other)
{
	if (other->T == Entity::Type::WALL)
	{
		Position = LastPosition;
	}
}

void Player::ChangeVelocity(double deltaTime) // Make into lua script
{
	const float MOVEMENT_SPEED = 500.0f;
	const float GRAVITY = 98.0f;

	int frameInputX = 0;

	if (KeyDown(Key::A) || KeyDown(Key::Left)) frameInputX -= 1;
	if (KeyDown(Key::D) || KeyDown(Key::Right))	frameInputX += 1;

	CurrentVelocity.x += frameInputX * (MOVEMENT_SPEED * deltaTime);
	CurrentVelocity.y += GRAVITY * deltaTime;
}
