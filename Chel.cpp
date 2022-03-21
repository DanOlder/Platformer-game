#include <SFML/Graphics.hpp>

#include "Constants.hpp"
#include "Map.hpp"
#include "Chel.hpp"
#include "Game.hpp"



Chel::Chel() {
	coords.x = 250;
	coords.y = 250;

	hitbox.left = coords.x;
	hitbox.top = coords.y;
	hitbox.width = 50.f;
	hitbox.height = 100.f;

	readyToJump = false;
	holdingSpaceTimer = 0.f;
	jumpHeight = 0.f;

	square.setSize((sf::Vector2f(hitbox.width, hitbox.height)));
	square.setFillColor(sf::Color(13, 19, 23));
}

sf::Vector2f Chel::getCoords() {
	return coords;
}
sf::FloatRect Chel::getHitbox() {
	hitbox.left = coords.x;
	hitbox.top = coords.y;
	return this->hitbox;
}

void Chel::getReadyToJump() {
	readyToJump = true;

	//start timer
	holdingSpaceTimerStart = chelClock.getElapsedTime().asSeconds();
	//printf("%f\n", holdingSpaceTimerStart);
}

void Chel::Jump() {
	//check timer 
	holdingSpaceTimer = (chelClock.getElapsedTime().asSeconds() - holdingSpaceTimerStart);
	//printf("%f\n", holdingSpaceTimer);
	if (holdingSpaceTimer > MAX_HOLDING_SPACE_TIME) holdingSpaceTimer = MAX_HOLDING_SPACE_TIME;
	jumpHeight = (holdingSpaceTimer / MAX_HOLDING_SPACE_TIME) * MAX_JUMP_HEIGHT;

	readyToJump = false;
}

void Chel::draw(sf::RenderWindow& window) {
	square.setPosition(coords.x, coords.y);
	window.draw(square);
}

void Chel::updating(Map* map) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)!=(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {	//XOR

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			float distance = map->checkCollision(coords, getHitbox(), CHEL_MAX_SPEED, RIGHT);
			if (distance < CHEL_MAX_SPEED) {
				coords.x += distance;
			}	
			else {
				coords.x += CHEL_MAX_SPEED;
			}
		}
		else {
			float distance = map->checkCollision(coords, getHitbox(), CHEL_MAX_SPEED, LEFT);
			if (distance < CHEL_MAX_SPEED) {
				coords.x -= distance;
			}
			else {
				coords.x -= CHEL_MAX_SPEED;
			}
		}
	}
	if (jumpHeight>0) {			//delete bool jumping?

		float distance = map->checkCollision(coords, getHitbox(), CHEL_JUMP_SPEED, UP);
		if (distance < CHEL_JUMP_SPEED) {
			if (jumpHeight >= distance) {
				coords.y -= distance;
				jumpHeight = 0;
			}
			else {
				coords.y -= jumpHeight;
				jumpHeight = 0;
			}
		}
		else {
			if (jumpHeight>=CHEL_JUMP_SPEED) {
				coords.y -= CHEL_JUMP_SPEED;
				jumpHeight -= CHEL_JUMP_SPEED;
			}
			else {
				coords.y -= jumpHeight;
				jumpHeight = 0;
			}
			
		}

	}
	/*else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) != (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))) {	//XOR

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			float distance = map->checkCollision(coords, getHitbox(), CHEL_JUMP_SPEED, UP);
			if (distance < CHEL_JUMP_SPEED) {
				coords.y -= distance;
			}
			else {
				coords.y -= CHEL_JUMP_SPEED;
			}
		}
		else {
			float distance = map->checkCollision(coords, DOWN);
			if (distance < CHEL_MAX_SPEED) {
				coords.y += distance;
			}
			else {
				coords.y += CHEL_MAX_SPEED;
			}
		}
	}*/
	else {
		float distance = map->checkCollision(coords, getHitbox(), GRAVITY, DOWN);
		if (distance < GRAVITY) {
			coords.y += distance;
		}
		else {
			coords.y += GRAVITY;
		}
	}

}

