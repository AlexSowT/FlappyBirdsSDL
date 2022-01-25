#include "TitleLayer.h"

TitleLayer::TitleLayer(RenderWindow p_window) : window(p_window)
{
}

void TitleLayer::init()
{
	active = true;
}

void TitleLayer::events(SDL_Event p_event)
{
	if (p_event.type == SDL_KEYDOWN)
	{
		if (active)
		{
			active = false;
		}
	} 
}

void TitleLayer::update(float p_deltaTime){}

void TitleLayer::render(float p_deltaTime)
{
	window.renderText(window.getWidth() / 2 - 250, window.getHeight() / 4, 500, 100, "Flappy SDL");
	window.renderText(window.getWidth() / 2 - 250, window.getHeight() / 4 + 150, 500 , 100, "Press any button to JUMP.");
	window.renderText(window.getWidth() / 2 - 250, window.getHeight() / 4 + 300, 500, 100, "Press any button to START.");
}