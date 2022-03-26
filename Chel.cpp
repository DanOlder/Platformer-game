#include <SFML/Graphics.hpp>

#include "Constants.hpp"
#include "Map.hpp"
#include "Chel.hpp"
#include "Game.hpp"



Chel::Chel() {
	coords.x = 935;
	coords.y = 700;

	speed_x = 0;
	speed_y = 0;

	hitbox.left = coords.x;
	hitbox.top = coords.y;
	hitbox.width = 50.f;
	hitbox.height = 100.f;

	readyToJump = false;
	inAir = true;
	holdingSpaceTimer = 0.f;

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
	speed_y = (holdingSpaceTimer / MAX_HOLDING_SPACE_TIME) * MAX_JUMP_SPEED;

	readyToJump = false;
	inAir = true;
}

void Chel::draw(sf::RenderWindow& window) {
	square.setPosition(coords.x, coords.y);
	window.draw(square);
}

void Chel::updating(Map* map) {

	if (inAir) {				//return when chel landed

		//y axis handling
		if (speed_y < 0) {

			float speed_mod = speed_y * (-1);

			float distance = map->checkCollision(coords, getHitbox(), speed_mod, DOWN);
			if (distance < speed_mod) {
				coords.y += distance;
				speed_y = 0;
				inAir = false;
				return;
			}
			else {
				coords.y += speed_mod;
			}
		}
		else if (speed_y > 0) {

			float distance = map->checkCollision(coords, getHitbox(), speed_y, UP);
			if (distance < speed_y) {
				coords.y -= distance;
				speed_y = 0;
			}
			else {
				coords.y -= speed_y;
			}
		}

		speed_y -= G;

	}
	else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) != (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {	//XOR

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				if (speed_x < CHEL_MAX_SPEED) {
					speed_x += CHEL_ACC;
				}
			}
			else {
				if (speed_x > -CHEL_MAX_SPEED) {
					speed_x -= CHEL_ACC;
				}
			}
		}
		//slowdown when no button's pressed
		else {
			if (speed_x > 0) {

				if (speed_x <= CHEL_ACC) {
					speed_x = 0;
				}
				else {
					speed_x -= CHEL_ACC;
				}
			}
			else if (speed_x < 0) {

				if (speed_x >= -CHEL_ACC) {
					speed_x = 0;
				}
				else {
					speed_x += CHEL_ACC;
				}
			}
		}
	}

	//checking if there are collisions then moving of character
	if (speed_x > 0) {
		float distance = map->checkCollision(coords, getHitbox(), speed_x, RIGHT);
		if (distance < speed_x) {
			coords.x += distance;
			speed_x = 0;
		}
		else {
			coords.x += speed_x;
		}
	}
	else if (speed_x < 0) {

		float speed_mod = speed_x * (-1);

		float distance = map->checkCollision(coords, getHitbox(), speed_mod, LEFT);
		if (distance < speed_mod) {
			coords.x -= distance;
			speed_x = 0;
		}
		else {
			coords.x -= speed_mod;
		}
	}

}

