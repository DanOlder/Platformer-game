#include <SFML/Graphics.hpp>

#include "Constants.hpp"
#include "GameTime.hpp"
#include "Animation.hpp"
#include "Map.hpp"
#include "Chel.hpp"
#include "Game.hpp"



Chel::Chel() {
	coords.x = 935;
	coords.y = 700;

	speed.x = 0;
	speed.y = 0;

	readyToJump = false;
	inAir = true;
	holdingSpaceTimer = 0.f;

	//animation (vector is how much sprites in the sheet(x and y))
	if (!chelTexture.loadFromFile("resources/test_sprites.png")) exit(666);
	chelShape.setSize((sf::Vector2f(CHEL_HITBOX_WIDHT, CHEL_HITBOX_HEIGHT)));
	chelShape.setTexture(&chelTexture);
	chelAnimation.init(&chelTexture, sf::Vector2u(4,1), 0.1f);
}

sf::Vector2f Chel::getCoords() {
	return coords;
}

bool Chel::isInAir()
{
	return inAir;
}


void Chel::getReadyToJump() {
	readyToJump = true;

	//start timer
	chelClock.restart().asSeconds();
	//printf("%f\n", holdingSpaceTimerStart);
}

void Chel::Jump() {
	//check timer 
	holdingSpaceTimer = chelClock.getElapsedTime().asSeconds();
	//printf("%f\n", holdingSpaceTimer);
	if (holdingSpaceTimer > MAX_HOLDING_SPACE_TIME) holdingSpaceTimer = MAX_HOLDING_SPACE_TIME;
	speed.y = (holdingSpaceTimer / MAX_HOLDING_SPACE_TIME) * MAX_JUMP_SPEED;

	readyToJump = false;
	inAir = true;
}

void Chel::draw(sf::RenderWindow& window) {

	//sprite
	chelShape.setPosition(coords);
	window.draw(chelShape);
}

void Chel::updating(Map* map, GameTime* gameTime) {

	//params in update are row and deltaTime
	chelAnimation.update(0,gameTime->deltaTime);//mb move in the end of method
	chelShape.setTextureRect(chelAnimation.spriteRect);

	if (inAir) {				//return when chel landed

		//y axis handling
		if (speed.y < 0) {

			coords.y -= speed.y;
			
			chelShape.setPosition(coords);
			if (map->checkCollision(chelShape.getGlobalBounds(), DOWN, &coords)) {
				speed.y = 0;
				inAir = false;
				return;
			}
		}
		else if (speed.y > 0) {

			coords.y -= speed.y;

			chelShape.setPosition(coords);
			if (map->checkCollision(chelShape.getGlobalBounds(), UP, &coords)) {
				speed.y = 0;
			}
		}
		speed.y -= G;
		if (speed.y < -MAX_FALLING_SPEED) {
			speed.y = -MAX_FALLING_SPEED;
		}

	}
	else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) != (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {	//XOR

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				if (speed.x < CHEL_MAX_SPEED) {
					speed.x += CHEL_ACC;
				}
			}
			else {
				if (speed.x > -CHEL_MAX_SPEED) {
					speed.x -= CHEL_ACC;
				}
			}
		}
		//slowdown when no button's pressed
		else {
			if (speed.x > 0) {

				if (speed.x <= CHEL_ACC) {
					speed.x = 0;
				}
				else {
					speed.x -= CHEL_ACC;
				}
			}
			else if (speed.x < 0) {

				if (speed.x >= -CHEL_ACC) {
					speed.x = 0;
				}
				else {
					speed.x += CHEL_ACC;
				}
			}
		}
		//check if there's no platforms under the character
		chelShape.setPosition(coords);
		sf::FloatRect tempRect = chelShape.getGlobalBounds();
		tempRect.top += 1;
		if (!(map->checkCollision(tempRect, DOWN, &coords))) {
			inAir = true;
		}
		////////////////////////////////////////////////////
	}

	//checking if there are collisions then moving of character
	if (speed.x > 0) {

		coords.x += speed.x;

		chelShape.setPosition(coords);
		if (map->checkCollision(chelShape.getGlobalBounds(), RIGHT, &coords)) {
			speed.x = -speed.x * 0.5f;
		}
	}
	else if (speed.x < 0) {

		coords.x += speed.x;

		chelShape.setPosition(coords);
		if (map->checkCollision(chelShape.getGlobalBounds(), LEFT, &coords)) {
			speed.x = -speed.x * 0.5f;
		}
	}

}

