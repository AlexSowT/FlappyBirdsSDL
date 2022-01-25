#include<SDL.h>
#include<SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "RenderWindow.h"
#include "MainGameLayer.h"
#include "Entity.h"
#include <vector>
#include <algorithm>
#include <string>


int main(int argv, char* args[])
{
	const int height = 768;
	const int width = 432 * 2;
	const int pipeSpawnCount = 6;
	const int pipeInitialPosition = 300;
	float backgroundSpeed = 0.15;
	float birdVelocity = 0.15;
	float birdRotation = 0;
	const float maxBirdVelocity = 0.4;
	const float gravity = 0.015;
	const float jumpSpped = -2;
	bool jumping = false;
	bool alive = true;
	const int maxDownRotation = 60;
	const int maxUpRotation = -50;
	const int pipeXSeperation = 200;
	const int pipeYSeperation = 100;
	int score = 0;

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) > 0)
	{
		std::cout << "SDL Init has filed. SDL_Error: " << SDL_GetError() << std::endl;
	}

	// Init PNG Loading
	if (!IMG_Init(IMG_INIT_PNG))
	{
		std::cout << "Image has failed to init. IMG_PNG_Error: " << SDL_GetError() << std::endl;
	}

	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}

	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}

	RenderWindow window("GAME v1.0", width, height);

	// Load Music
	Mix_Music* gameMusic = Mix_LoadMUS("../gfx/main_music.mp3");

	MainGameLayer gameLayer(window);

	// Init the layers
	gameLayer.init();

	bool running = true;

	SDL_Event event;

	float currentTime = SDL_GetTicks();

	Mix_PlayMusic(gameMusic, -1);

	while (running)
	{
		float newTime = SDL_GetTicks();
		float deltaTime = newTime - currentTime;
		currentTime = newTime;

		// Events
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}

			if (gameLayer.getAlive())
			{
				gameLayer.events(event);
			}
			else
			{
				if (event.type == SDL_KEYDOWN)
				{
					gameLayer.init();
				}
			}
		}

		if (gameLayer.getAlive())
		{
			gameLayer.update(deltaTime);
		}

		// Render
		window.clear();
		gameLayer.render(deltaTime);
		window.display();
	}

	Mix_FreeMusic(gameMusic);
	gameMusic = NULL;
	window.cleanUp();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;
}