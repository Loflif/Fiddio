#include <iostream>
#include "Fiddio.h"

const static double DELTA_TIME = 1 / 100.0; // Desired time per simulated tick

int main(int argc, char* args[])
{
	Fiddio game;

	FRAME_NUM = 0;

	double currentTime = static_cast<double>(SDL_GetPerformanceCounter()) / SDL_GetPerformanceFrequency();
	double remainingFrameTime = 0;

	while (game.Running())
	{
		double refreshedTime = static_cast<double>(SDL_GetPerformanceCounter()) / SDL_GetPerformanceFrequency();
		double frameTime = refreshedTime - currentTime;

		game.HandleEvents();

		currentTime = refreshedTime;

		remainingFrameTime += frameTime;

		while (remainingFrameTime >= DELTA_TIME)
		{
			game.Update();
			game.CheckCollisions();
			remainingFrameTime -= DELTA_TIME;
			FRAME_NUM++;
		}

		while (frameTime < DELTA_TIME) // Too fast
		{
			double sleepDuration = DELTA_TIME - frameTime;
			SDL_Delay(sleepDuration);
			frameTime += sleepDuration;
		}
		game.Render();
	}
	return 0;
}