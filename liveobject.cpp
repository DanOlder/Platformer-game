#include "Hyperheader.hpp"

liveObject::liveObject(sf::Vector2f pos)
{
	speed.x = 0.f;
	speed.y = 0.f;

	setPosition(pos);
}

//in blocks
void liveObject::setPosition(sf::Vector2f pos)
{
	
	coords.x = pos.x * BLOCK_SIZE;
	coords.y = pos.y * BLOCK_SIZE;
}

sf::Vector2f liveObject::getCoords()
{
	return coords;
}

sf::FloatRect liveObject::getSpriteRect()
{
	return hitbox.getGlobalBounds();
}

void liveObject::draw(sf::RenderWindow& window)
{
	//sprite
	hitbox.setPosition(coords);
	window.draw(hitbox);
}
