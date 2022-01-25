#pragma once
#include "iLayer.h"
#include "RenderWindow.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include <vector>
class TitleLayer : public ILayer
{
public:
	TitleLayer(RenderWindow p_window);

	void init();
	void events(SDL_Event p_event);
	void update(float p_deltaTime);
	void render(float p_deltaTime);

	bool getActive() { return active; }

private:
	// TODO: Can I pass by reference or pointer here? 
	RenderWindow window;
	bool active;
};
