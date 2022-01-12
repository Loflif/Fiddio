#pragma once
#include <SDL/SDL.h>
#include "Key.h"
#include "Vector2.h"

// Being set through lua to avoid compiling
static int WINDOW_WIDTH;
static int WINDOW_HEIGHT;

static Vector2 SCREEN_CENTER;

const static char* GAME_TITLE;

extern const double DELTA_TIME;

class Player;
class Entity;

class Fiddio
{
public:
	Fiddio();
	~Fiddio();

	void HandleEvents();
	void Update();
	void Render();
	void CheckCollisions();

	bool Running() { return IsRunning; }
	
private:
	void Init();
	void AddCollisionPairs();

	bool IsRunning = false;
	
	SDL_Window* Window = nullptr;
	SDL_Renderer* Renderer = nullptr;

	double timePlaying = 0.0;
};

extern Uint64 FRAME_NUM;

bool KeyDown(Key key);
bool KeyPressed(Key key);
bool KeyReleased(Key key);
