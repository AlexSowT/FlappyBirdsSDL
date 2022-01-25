#pragma once
#include <SDL.h>
#include <SDL_image.h>


class Entity
{
public:
	Entity(float p_x, float p_y, float p_w, float p_h, float p_scale, SDL_Texture* p_texture);
	float getX() { return x; }
	float getY() { return y; }
	SDL_Rect getCurrentFrame() { return currentFrame; }
	SDL_Texture* getTexture() { return texture; };

	void setX(float p_x);
	void setY(float p_y);

	bool checkCollision(Entity& body);

private:
	float x, y, w, h;
	SDL_Rect currentFrame;
	SDL_Texture* texture;
};