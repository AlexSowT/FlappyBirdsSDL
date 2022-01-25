#include "Entity.h"

Entity::Entity(float p_x, float p_y, float p_w, float p_h, float p_scale, SDL_Texture* p_texture)
	: x(p_x), y(p_y), w(p_w * p_scale), h(p_h * p_scale), texture(p_texture)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = w;
	currentFrame.h = h;
}

void Entity::setX(float p_x)
{ 
	x = p_x; 
	//currentFrame.x = x;
}

void Entity::setY(float p_y)
{ 
	y = p_y;
	//currentFrame.y = y;
}

bool Entity::checkCollision(Entity& body)
{
	if (x < body.x + body.w &&
		x + w > body.x &&
		y < body.y + body.h &&
		y + h > body.y)
		return true;

	return false;
}