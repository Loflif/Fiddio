#include <iostream>
#include "Fiddio.h"

const static double TARGET_FRAME_SECONDS = 1 / 60.0; // Desired time per simulated tick

int main(int argc, char* args[])
{
	Fiddio game;

	double currentTime = static_cast<double>(SDL_GetPerformanceCounter()) / SDL_GetPerformanceFrequency();
	double remainingFrameTime = 0;

	while (game.Running())
	{
		Uint64 startTick = SDL_GetPerformanceCounter();

		double refreshedTime = static_cast<double>(SDL_GetPerformanceCounter()) / SDL_GetPerformanceFrequency();
		double frameTime = refreshedTime - currentTime;

		game.HandleEvents();

		currentTime = refreshedTime;

		remainingFrameTime += frameTime;

		while (remainingFrameTime >= TARGET_FRAME_SECONDS)
		{
			game.CheckCollisions();
			game.Update(TARGET_FRAME_SECONDS);
			remainingFrameTime -= TARGET_FRAME_SECONDS;
		}

		while (frameTime < TARGET_FRAME_SECONDS) // Too fast
		{
			double sleepDuration = TARGET_FRAME_SECONDS - frameTime;
			SDL_Delay(sleepDuration);
			frameTime += sleepDuration;
		}
		game.Render();
	}
	return 0;
}