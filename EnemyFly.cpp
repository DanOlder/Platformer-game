#include "Hyperheader.hpp"



EnemyFly::EnemyFly(sf::Vector2f pos) : liveObject(pos) {

	speed.x = 20;
	speed.y = 0;

	//animation (vector is how much sprites in the sheet(x and y))
	if (!flyTexture.loadFromFile("resources/test_sprites.png")) exit(666);
	hitbox.setSize((sf::Vector2f(BAT_HITBOX_WIDHT, BAT_HITBOX_HEIGHT)));
	hitbox.setTexture(&flyTexture);
	//animation.init(&flyTexture, sf::Vector2u(11, 1), 0.1f);
}

void EnemyFly::updating(Map* map , GameTime* gameTime)
{

	//params in update are row and deltaTime
	//animation.update(0, gameTime->deltaTime);//mb move in the end of method
	//hitbox.setTextureRect(animation.spriteRect);


	//checking if there are collisions then moving of character
	if (speed.x > 0) {

		coords.x += speed.x;

		hitbox.setPosition(coords);
		if (map->checkCollision(hitbox.getGlobalBounds(), RIGHT, &coords)) {
			speed.x = -speed.x;
		}
	}
	else if (speed.x < 0) {

		coords.x += speed.x;

		hitbox.setPosition(coords);
		if (map->checkCollision(hitbox.getGlobalBounds(), LEFT, &coords)) {
			speed.x = -speed.x;
		}
	}


}
