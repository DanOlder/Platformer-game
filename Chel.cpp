#include "Hyperheader.hpp"

Chel::Chel(sf::Vector2f pos) : liveObject(pos) {

	speed.x = 0;
	speed.y = 0;

	readyToJump = false;
	inAir = true;
	holdingSpaceTimer = 0.f;

	//animation (vector is how much sprites in the sheet(x and y))
	if (!chelTexture.loadFromFile("resources/test_sprites.png")) exit(666);
	hitbox.setSize((sf::Vector2f(CHEL_HITBOX_WIDHT, CHEL_HITBOX_HEIGHT)));
	hitbox.setTexture(&chelTexture);
	animation.init(&chelTexture, sf::Vector2u(4,1), 0.1f);
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

void Chel::updating(Map* map, GameTime* gameTime) {

	//params in update are row and deltaTime
	animation.update(0,gameTime->deltaTime);//mb move in the end of method
	hitbox.setTextureRect(animation.spriteRect);

	if (inAir) {				//return when chel landed

		//y axis handling
		if (speed.y < 0) {

			coords.y -= speed.y;
			
			hitbox.setPosition(coords);
			if (map->checkCollision(hitbox.getGlobalBounds(), DOWN, &coords)) {
				speed.y = 0;
				inAir = false;
				return;
			}
		}
		else if (speed.y > 0) {

			coords.y -= speed.y;

			hitbox.setPosition(coords);
			if (map->checkCollision(hitbox.getGlobalBounds(), UP, &coords)) {
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
		hitbox.setPosition(coords);
		sf::FloatRect tempRect = hitbox.getGlobalBounds();
		tempRect.top += 1;
		if (!(map->checkCollision(tempRect, DOWN, &coords))) {
			inAir = true;
		}
		////////////////////////////////////////////////////
	}

	//checking if there are collisions then moving of character
	if (speed.x > 0) {

		coords.x += speed.x;

		hitbox.setPosition(coords);
		if (map->checkCollision(hitbox.getGlobalBounds(), RIGHT, &coords)) {
			speed.x = -speed.x * BOUNCE_RATIO;
		}
	}
	else if (speed.x < 0) {

		coords.x += speed.x;

		hitbox.setPosition(coords);
		if (map->checkCollision(hitbox.getGlobalBounds(), LEFT, &coords)) {
			speed.x = -speed.x * BOUNCE_RATIO;
		}
	}

}

