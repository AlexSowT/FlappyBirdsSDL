#include "MainGameLayer.h"

MainGameLayer::MainGameLayer(RenderWindow p_window): window(p_window), bird01Texture(window.loadTexture("../gfx/bird_1.png")), bird(100, 768 / 2, 19, 19, 2, bird01Texture){
	backgroundTexture = window.loadTexture("../gfx/background_day.png");
	pipeDownTexture = window.loadTexture("../gfx/pipe_down.png");
	pipeUpTexture = window.loadTexture("../gfx/pipe_up.png");
	jumpSound = Mix_LoadWAV("../gfx/jump.wav");
	hitSound = Mix_LoadWAV("../gfx/hit.wav");
}

void MainGameLayer::init()
{
	alive = true;
	elapsed = 0;
	score = 0;

	backgrounds.clear();
	downPipes.clear();
	upPipes.clear();

	backgrounds = {
		Entity(432 * 2, 0, 432, 768, 1, backgroundTexture),
		Entity(0, 0, 432, 768, 1, backgroundTexture),
		Entity(432, 0, 432, 768, 1, backgroundTexture)
	};

	for (int pipe_count = 0; pipe_count < pipeSpawnCount; ++pipe_count)
	{
		float yPos = rand() % 400 + 50;

		downPipes.push_back(Entity(pipeInitialPosition + (pipeXSeperation * pipe_count), -yPos, 26, 160, 3, pipeDownTexture));
		upPipes.push_back(Entity(pipeInitialPosition + (pipeXSeperation * pipe_count), window.getHeight() - yPos, 26, 160, 3, pipeUpTexture));
	}

	bird.setX(100);
	bird.setY(window.getHeight() / 2);
}

void MainGameLayer::events(SDL_Event p_event) {
	if (p_event.type == SDL_KEYDOWN)
	{
		if (!jumping)
		{
			birdVelocity = jumpSpeed;
			jumping = true;
			Mix_PlayChannel(-1, jumpSound, 0);
		}

		if (!alive)
		{
			// Reset the game here.

		}
	} else if (p_event.type == SDL_KEYUP)
	{
		jumping = false;
	}
}

void MainGameLayer::update(float p_deltaTime){
	elapsed += p_deltaTime;

	for (auto background_i = 0; background_i < backgrounds.size(); ++background_i)
	{
		backgrounds[background_i].setX(backgrounds[background_i].getX() - backgroundSpeed * p_deltaTime);
		if (backgrounds[background_i].getX() <= -window.getWidth() / 2)
		{
			backgrounds[background_i].setX(window.getWidth());
		}

	}

	for (auto pipe_i = 0; pipe_i < pipeSpawnCount; ++pipe_i)
	{
		if (downPipes[pipe_i].checkCollision(bird))
		{
			alive = false;
			Mix_PlayChannel(-1, hitSound, 0);
		}

		if (upPipes[pipe_i].checkCollision(bird))
		{
			alive = false;
			Mix_PlayChannel(-1, hitSound, 0);
		}

		downPipes[pipe_i].setX(downPipes[pipe_i].getX() - backgroundSpeed * p_deltaTime);
		upPipes[pipe_i].setX(upPipes[pipe_i].getX() - backgroundSpeed * p_deltaTime);

		if (upPipes[pipe_i].getX() <= -window.getWidth() / 2)
		{
			float yPos = rand() % 400 + 50;

			upPipes[pipe_i].setX(window.getWidth());
			downPipes[pipe_i].setX(window.getWidth());
			upPipes[pipe_i].setY(window.getHeight() - yPos);
			downPipes[pipe_i].setY(-yPos);
		}
	}

	bird.setY(bird.getY() + birdVelocity * p_deltaTime);

	if (birdVelocity < maxBirdVelocity)
		birdVelocity += gravity * p_deltaTime;

	birdRotation += birdVelocity * p_deltaTime;

	birdRotation = SDL_clamp(birdRotation, maxUpRotation, maxDownRotation);

	score = elapsed / 1000;
}

void MainGameLayer::render(float p_deltaTime) {

	for (auto background_i = 0; background_i < backgrounds.size(); ++background_i)
	{
		window.render(backgrounds[background_i], 0);
	}

	for (auto pipeDown_i = 0; pipeDown_i < downPipes.size(); ++pipeDown_i)
	{
		window.render(downPipes[pipeDown_i], 0);
	}

	for (auto pipeUp_i = 0; pipeUp_i < upPipes.size(); ++pipeUp_i)
	{
		window.render(upPipes[pipeUp_i], 0);
	}

	if (alive)
	{
		window.renderText(window.getWidth() / 2 - 30, window.getHeight() / 8, 100, 100, std::to_string(score).c_str());
	}
	else
	{
		std::stringstream scoreMessage;
		scoreMessage << "Score: " << std::to_string(score);
		window.renderText(window.getWidth() / 2 - 100, window.getHeight() / 4, 200, 100, "Game Over!");
		window.renderText(window.getWidth() / 2 - 100, window.getHeight() / 4 + 150, 200, 100, scoreMessage.str().c_str());
		window.renderText(window.getWidth() / 2 - 250, window.getHeight() / 4 + 300, 500, 100, "Press any button to restart");

	}
	window.render(bird, birdRotation);
}