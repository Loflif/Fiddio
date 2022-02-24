#include "Fiddio.h"

#include "CollisionHandler.h"
#include "ScriptHandler.h"
#include "LevelHandler.h"
#include "Player.h"

#include <iostream>

struct KeyState
{
	bool IsPressed = false;
	int ChangeFrame = 0;
};
KeyState KEY_STATES[(int)Key::MAX];

Uint64 FRAME_NUM = 0;

Fiddio::Fiddio()
{
	Init();
	AddCollisionPairs();
}

void Fiddio::Init()
{
	ScriptHandler::Init();
	LevelHandler::Init();

	WINDOW_WIDTH = ScriptHandler::GetTableInt("src/Settings.lua", "settings", "WindowWidth");
	WINDOW_HEIGHT = ScriptHandler::GetTableInt("src/Settings.lua", "settings", "WindowHeight");
	WINDOW_SCROLL_THRESHOLD = ScriptHandler::GetTableInt("src/Settings.lua", "settings", "WindowScrollThreshold");
	GAME_TITLE = ScriptHandler::GetTableString("src/Settings.lua", "settings", "GameTitle");

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << SDL_GetError() << std::endl;
		return;
	}

	Window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if (Window == NULL)
	{
		std::cout << SDL_GetError() << std::endl;
		return;
	}

	Renderer = SDL_CreateRenderer(Window, -1, 0);
	if (Renderer == NULL)
	{
		std::cout << SDL_GetError() << std::endl;
		return;
	}

	SDL_SetRenderDrawColor(Renderer, 146, 144, 255, 1);

	IsRunning = true;

}

void Fiddio::AddCollisionPairs()
{
	CollisionHandler::AddCollisionPair(std::pair<EntityType, EntityType>(EntityType::PLAYER, EntityType::WALL));
	CollisionHandler::AddCollisionPair(std::pair<EntityType, EntityType>(EntityType::PLAYER, EntityType::PIPE));
	CollisionHandler::AddCollisionPair(std::pair<EntityType, EntityType>(EntityType::PLAYER, EntityType::GOOMBA));
	CollisionHandler::AddCollisionPair(std::pair<EntityType, EntityType>(EntityType::PLAYER, EntityType::FLOATING_BLOCK));
	CollisionHandler::AddCollisionPair(std::pair<EntityType, EntityType>(EntityType::PLAYER, EntityType::GROUND_BLOCK));
	CollisionHandler::AddCollisionPair(std::pair<EntityType, EntityType>(EntityType::PLAYER, EntityType::MOVING_PLATFORM));
}

void Fiddio::HandleCamera()
{
	float desiredScreenPosition = CAMERA_POS.x + WINDOW_SCROLL_THRESHOLD;
	if (PLAYER->Position.x > desiredScreenPosition)
	{
		CAMERA_POS.x += PLAYER->Position.x - desiredScreenPosition;
	}
}

void Fiddio::ConstrainPlayer()
{
	if (PLAYER->Position.x < CAMERA_POS.x)
	{
		PLAYER->Position.x = CAMERA_POS.x;
		PLAYER->CurrentVelocity.x = 0.0f;
	}
}


Fiddio::~Fiddio()
{
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	SDL_Quit();
	LevelHandler::CleanUp();
	ScriptHandler::CleanUp();
}

void Fiddio::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
		case SDL_QUIT: IsRunning = false; break;
		case SDL_KEYDOWN:
		{
			// Don't care about repeats....
			if (event.key.repeat)
				break;

			int scanCode = event.key.keysym.scancode;
			KEY_STATES[scanCode].IsPressed = true;
			KEY_STATES[scanCode].ChangeFrame = FRAME_NUM;
			break;
		}
		case SDL_KEYUP:
		{
			int scanCode = event.key.keysym.scancode;
			KEY_STATES[scanCode].IsPressed = false;
			KEY_STATES[scanCode].ChangeFrame = FRAME_NUM;
			break;
		}
		default: break;
	}
}

void Fiddio::Update()
{
	for (auto& entity : DYNAMIC_ENTITIES)
	{
		if (!entity->IsActive)
			continue;

		entity->Update();
	}

	HandleCamera();
	ConstrainPlayer();
}

void Fiddio::Render()
{
	SDL_SetRenderDrawColor(Renderer, 92, 148, 252, 1);
	SDL_RenderClear(Renderer);

	for (auto& entity : STATIC_ENTITIES)
	{
		if (!entity->IsVisible)
			continue;

		entity->Render(Renderer, -CAMERA_POS);
	}

	for (auto& entity : DYNAMIC_ENTITIES)
	{
		if (!entity->IsVisible)
			continue;

		entity->Render(Renderer, -CAMERA_POS);
	}

	SDL_RenderPresent(Renderer);
}

void Fiddio::CheckCollisions()
{
	CollisionHandler::CheckCollisions(DYNAMIC_ENTITIES, STATIC_ENTITIES);
}

bool KeyDown(Key key)
{
	return KEY_STATES[(int)key].IsPressed;
}
bool KeyPressed(Key key)
{
	return KEY_STATES[(int)key].IsPressed && KEY_STATES[(int)key].ChangeFrame == FRAME_NUM;
}
bool KeyReleased(Key key)
{
	return !KEY_STATES[(int)key].IsPressed && KEY_STATES[(int)key].ChangeFrame == FRAME_NUM;
}