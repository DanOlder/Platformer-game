#include <SFML/Graphics.hpp>
#include <algorithm>

#include "Constants.hpp"
#include "GameTime.hpp"
#include "Animation.hpp"
#include "Map.hpp"
#include "Chel.hpp"
#include "Game.hpp"

Map::Map() {

	sf::Color clr = sf::Color(155, 100, 60);

	//size in blocks, position in blocks, and color
	addPlatform(sf::Vector2f(32.f, 1.f), sf::Vector2f(0.f, 17.f), clr);
	addPlatform(sf::Vector2f(32.f, 1.f), sf::Vector2f(0.f, 0.f), clr);
	addPlatform(sf::Vector2f(1.f, 18.f), sf::Vector2f(0.f, 0.f), clr);
	addPlatform(sf::Vector2f(1.f, 18.f), sf::Vector2f(31.f, 0.f), clr);

	addPlatform(sf::Vector2f(5.f, 1.f), sf::Vector2f(5.f, 3.f), clr);
	addPlatform(sf::Vector2f(5.f, 1.f), sf::Vector2f(10.f, 8.f), clr);
	addPlatform(sf::Vector2f(5.f, 1.f), sf::Vector2f(15.f, 11.f), clr);
	addPlatform(sf::Vector2f(5.f, 1.f), sf::Vector2f(20.f, 15.f), clr);
}

void Map::addPlatform(sf::Vector2f size, sf::Vector2f position, sf::Color color) {	//sprite will be instead of color

	size.x *= BLOCK_SIZE;
	size.y *= BLOCK_SIZE;
	position.x *= BLOCK_SIZE;
	position.y *= BLOCK_SIZE;

	sf::RectangleShape platform;

	platform.setSize(size);
	platform.setPosition(position);
	platform.setFillColor(color);

	platforms.push_back(platform);
}

void Map::draw(sf::RenderWindow& window) {

	//draw only if object is on the screen

	for (auto& i : platforms) {
		window.draw(i);
	}
}



bool Map::checkCollision(sf::FloatRect hitbox, Directions dir, sf::Vector2f* pos) {
	if (dir == LEFT) {
		for (auto& i : platforms) {
			sf::FloatRect tempRect = i.getGlobalBounds();
			if (tempRect.intersects(hitbox)) {
				do {
					hitbox.left += 1;
				} while (tempRect.intersects(hitbox));
				pos->x = hitbox.left;
				return true;
			}
		}
	}
	else if (dir == RIGHT) {
		for (auto& i : platforms) {
			sf::FloatRect tempRect = i.getGlobalBounds();
			if (tempRect.intersects(hitbox)) {
				do {
					hitbox.left -= 1;
				} while (tempRect.intersects(hitbox));
				pos->x = hitbox.left;
				return true;
			}
		}
	}
	else if (dir == UP) {
		for (auto& i : platforms) {
			sf::FloatRect tempRect = i.getGlobalBounds();
			if (tempRect.intersects(hitbox)) {
				do {
					hitbox.top += 1;
				} while (tempRect.intersects(hitbox));
				pos->y = hitbox.top;
				return true;
			}
		}
	}
	else if (dir == DOWN) {
		for (auto& i : platforms) {
			sf::FloatRect tempRect = i.getGlobalBounds();
			if (tempRect.intersects(hitbox)) {
				do {
					hitbox.top -= 1;
				} while (tempRect.intersects(hitbox));
				pos->y = hitbox.top;
				return true;
			}
		}
	}

	return false;





	/*
	if (dir == LEFT) {
		hitbox.left -= speed;



		for (auto& i : platforms) {
			sf::FloatRect tempRect = i.getGlobalBounds();
			if (tempRect.intersects(hitbox)) {

			}
		}



		if (lwall.intersects(hitbox)){
			return (hitbox.left+speed) - (lwall.left+lwall.width); 
		}
		else return speed;
	}
	else if (dir == RIGHT) {
		hitbox.left += speed;
		if (rwall.intersects(hitbox)){
			return rwall.left - (hitbox.left-speed+hitbox.width);
		}
		else return speed;
	}
	else if (dir == UP) {
		hitbox.top -= speed;
		if (ceiling.intersects(hitbox)){
			return (hitbox.top + speed) - (ceiling.top + ceiling.height);
		}
		else return speed;
	}
	else if (dir == DOWN) {
		hitbox.top += speed;
		if (floor.intersects(hitbox)){
			return floor.top - (hitbox.top-speed+hitbox.height);
		}
		else return speed;
	}
	*/

}