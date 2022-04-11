#include <SFML/Graphics.hpp>
#include <algorithm>

#include "Constants.hpp"
#include "GameTime.hpp"
#include "Animation.hpp"
#include "Map.hpp"
#include "Chel.hpp"
#include "Game.hpp"

Map::Map() {

	screenCounter = 1;

	//for this demo will be made 1 level with 5 screens

	sf::Color clr = sf::Color(155, 100, 60);

	//size in blocks, position in blocks, and color
	//walls and floor
	addPlatform(sf::Vector2f(32.f, 1.f), sf::Vector2f(0.f, 17.f), clr);
	addPlatform(sf::Vector2f(32.f, 1.f), sf::Vector2f(0.f, -72.f), clr);
	addPlatform(sf::Vector2f(1.f, 90.f), sf::Vector2f(0.f, -72.f), clr);
	addPlatform(sf::Vector2f(1.f, 90.f), sf::Vector2f(31.f, -72.f), clr);

	//first screen platforms
	addPlatform(sf::Vector2f(5.f, 1.f), sf::Vector2f(5.f, 3.f), clr);
	addPlatform(sf::Vector2f(5.f, 1.f), sf::Vector2f(10.f, 8.f), clr);
	addPlatform(sf::Vector2f(5.f, 1.f), sf::Vector2f(15.f, 11.f), clr);
	addPlatform(sf::Vector2f(5.f, 1.f), sf::Vector2f(20.f, 15.f), clr);

	//second screen platforms	
	addPlatform(sf::Vector2f(5.f, 1.f), sf::Vector2f(20.f, 3.f-18.f), clr);
	addPlatform(sf::Vector2f(5.f, 1.f), sf::Vector2f(15.f, 8.f - 18.f), clr);
	addPlatform(sf::Vector2f(5.f, 1.f), sf::Vector2f(10.f, 11.f - 18.f), clr);
	addPlatform(sf::Vector2f(5.f, 1.f), sf::Vector2f(8.f, 15.f - 18.f), clr);

	//third screen platforms
	addPlatform(sf::Vector2f(5.f, 1.f), sf::Vector2f(5.f, 3.f - 36.f), clr);
	addPlatform(sf::Vector2f(5.f, 1.f), sf::Vector2f(10.f, 8.f - 36.f), clr);
	addPlatform(sf::Vector2f(5.f, 1.f), sf::Vector2f(15.f, 11.f - 36.f), clr);
	addPlatform(sf::Vector2f(5.f, 1.f), sf::Vector2f(22.f, 15.f - 36.f), clr);

	//fifth screen platforms
	addPlatform(sf::Vector2f(5.f, 1.f), sf::Vector2f(20.f, 3.f - 54.f), clr);
	addPlatform(sf::Vector2f(5.f, 1.f), sf::Vector2f(15.f, 8.f - 54.f), clr);
	addPlatform(sf::Vector2f(5.f, 1.f), sf::Vector2f(10.f, 11.f - 54.f), clr);
	addPlatform(sf::Vector2f(5.f, 1.f), sf::Vector2f(0.f, 15.f - 54.f), clr);
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

void Map::lastPhaseInit() {
	//for only first level
	addPlatform(sf::Vector2f(32.f, 1.f), sf::Vector2f(0.f, -55.f), sf::Color(155, 100, 60));
}

void Map::updating(sf::FloatRect chelRect, sf::View* view, sf::Vector2f screenSize) {
	//watch top border of screen and bottom border of screen and then check if the character in this area

	float topBorder = 0 - screenCounter * DEF_HEIGHT;
	float bottomBorder = DEF_HEIGHT - screenCounter * DEF_HEIGHT;

	//*2 for placing the floor on the last screen
	if (chelRect.top + chelRect.height *2 < topBorder) {
		sf::Vector2f oldCenter = view->getCenter();
		view->setCenter(oldCenter.x, oldCenter.y - DEF_HEIGHT);
		view->move(0.f, 0.f);
		screenCounter++;
		if (screenCounter == 5) {
			lastPhaseInit();
		}
	}
	else if (chelRect.top > bottomBorder) {
		sf::Vector2f oldCenter = view->getCenter();
		view->setCenter(oldCenter.x, oldCenter.y + DEF_HEIGHT);
		view->move(0.f, 0.f);
		screenCounter--;
	}
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
}