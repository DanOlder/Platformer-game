#include <SFML/Graphics.hpp>

#include "Constants.hpp"
#include "Map.hpp"
#include "Chel.hpp"
#include "Game.hpp"



Chel::Chel() {
	coords.x = 250;
	coords.y = 250;

	square.setSize((sf::Vector2f(50.f, 50.f)));
	square.setFillColor(sf::Color(13, 19, 23));
}

sf::Vector2f Chel::getCoords() {
	return coords;
}

void Chel::draw(sf::RenderWindow& window) {
	square.setPosition(coords.x, coords.y);
	window.draw(square);
}

void Chel::updating(Map* map) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)!=(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {	//XOR

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			float distance = map->checkCollision(coords, RIGHT);
			if (distance < CHEL_MAX_SPEED) {
				coords.x += distance;
			}	
			else {
				coords.x += CHEL_MAX_SPEED;
			}
		}
		else {
			float distance = map->checkCollision(coords, LEFT);
			if (distance < CHEL_MAX_SPEED) {
				coords.x -= distance;
			}
			else {
				coords.x -= CHEL_MAX_SPEED;
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) != (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))) {	//XOR

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			float distance = map->checkCollision(coords, UP);
			if (distance < CHEL_VERTICAL_SPEED) {
				coords.y -= distance;
			}
			else {
				coords.y -= CHEL_MAX_SPEED;
			}
		}
		/*else {
			float distance = map->checkCollision(coords, DOWN);
			if (distance < CHEL_MAX_SPEED) {
				coords.y += distance;
			}
			else {
				coords.y += CHEL_MAX_SPEED;
			}
		}*/
	}
	else {
		float distance = map->checkCollision(coords, DOWN);
		if (distance < GRAVITY) {
			coords.y += distance;
		}
		else {
			coords.y += GRAVITY;
		}
	}


	
}