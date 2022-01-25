#pragma once
#include "iLayer.h"
#include "RenderWindow.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include <string>
#include <sstream>
class MainGameLayer : public ILayer
{
public:
	MainGameLayer(RenderWindow p_window);

	void init();
	void events(SDL_Event p_event);
	void update(float p_deltaTime);
	void render(float p_deltaTime);

	bool getAlive() { return alive; }
private:
	// TODO: Can I pass by reference or pointer here? 
	RenderWindow window;
	SDL_Texture* backgroundTexture;
	SDL_Texture* bird01Texture;
	SDL_Texture* pipeDownTexture;
	SDL_Texture* pipeUpTexture;

	Mix_Chunk* jumpSound;
	Mix_Chunk* hitSound;

	Entity bird;

	std::vector<Entity> backgrounds;
	std::vector<Entity> downPipes;
	std::vector<Entity> upPipes;

	const int pipeXSeperation = 200;
	const int pipeYSeperation = 100;
	const int pipeSpawnCount = 6;
	const int pipeInitialPosition = 300;

	bool alive = true;

	float backgroundSpeed = 0.15;
	float birdVelocity = 0.15;
	float birdRotation = 0;
	const float maxBirdVelocity = 0.4;
	const float gravity = 0.015;
	const float jumpSpeed = -2;
	const int maxDownRotation = 60;
	const int maxUpRotation = -50;

	int score = 0;
	bool jumping = false;

	float elapsed = 0;
};
