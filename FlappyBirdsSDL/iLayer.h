#pragma once
#include <SDL.h>
class ILayer
{
public:
	virtual void init() = 0;
	virtual void events(SDL_Event p_event) = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render(float deltaTime) = 0;
private:
};