#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Entity.h"

class RenderWindow {
public:
	RenderWindow(const char* p_title, int p_w, int p_h);

	SDL_Texture* loadTexture(const char* p_filePath);
	void clear();
	void render(Entity& p_entity, float angle);
	void display();
	void cleanUp();
	void renderText(float p_x, float p_y, float p_w, float p_h, const char* p_text);

	int getWidth() { return width; }
	int getHeight() { return height; }
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Color white;

	int width; 
	int height;
};