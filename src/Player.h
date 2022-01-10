#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
    Player(Vector2 spawnPos, SDL_Color color, Vector2 colliderSize, bool activate = true);
    virtual void Update(double deltaTime) override;
    virtual void OnCollision(Entity* other) override;

private:
    void ChangeVelocity(double deltaTime);

    Vector2 CurrentVelocity = Vector2(0, 0);
    Vector2 LastPosition = Vector2(0, 0);
};

