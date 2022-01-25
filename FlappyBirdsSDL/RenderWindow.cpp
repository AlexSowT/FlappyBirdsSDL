#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "RenderWindow.h"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL), width(p_w), height(p_h)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
	{
		std::cout << "Renderer failed to init. Error: " << SDL_GetError() << std::endl;
	}

	font = TTF_OpenFont("../gfx/flappy-font.ttf", 24);
	white = { 255, 255, 255 };
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == NULL)
	{
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
	}

	return texture;
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& p_entity, float angle)
{
	SDL_Rect src;
	src.x = p_entity.getCurrentFrame().x; 
	src.y = p_entity.getCurrentFrame().y;
	//src.x = 0; 
	//src.y = 0;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dest;
	dest.x = p_entity.getX();
	dest.y = p_entity.getY();
	dest.w = p_entity.getCurrentFrame().w;
	dest.h = p_entity.getCurrentFrame().h;

	//SDL_RenderCopy(renderer, p_entity.getTexture(), &src , &dest);
	SDL_RenderCopyEx(renderer, p_entity.getTexture(), &src, &dest, angle, NULL, SDL_FLIP_NONE);

}

void RenderWindow::renderText(float p_x, float p_y, float p_w, float p_h, const char* p_text)
{
	SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, p_text, white);
	if (scoreSurface == NULL)
	{
		std::cout << "Unable to render Text Surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
	}
	SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);

	SDL_Rect messageRect; //create a rect
	messageRect.x = p_x;  //controls the rect's x coordinate 
	messageRect.y = p_y; // controls the rect's y coordinte
	messageRect.w = p_w; // controls the width of the rect
	messageRect.h = p_h; // controls the height of the rect

	SDL_RenderCopy(renderer, scoreTexture, NULL, &messageRect);

	// Don't forget to free your surface and texture
	//SDL_FreeSurface(scoreSurface);
	//SDL_DestroyTexture(scoreTexture);
}


void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}