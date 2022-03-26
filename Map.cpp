#include <SFML/Graphics.hpp>
#include <algorithm>

#include "Constants.hpp"
#include "Map.hpp"
#include "Chel.hpp"
#include "Game.hpp"

Map::Map() {
	floor.left = 0;
	floor.top = 1060;
	floor.height = 100;
	floor.width = 1980;

	ceiling.left = 0;
	ceiling.top = -100;
	ceiling.height = 120;
	ceiling.width = 1980;

	lwall.left = -100;
	lwall.top = 0;
	lwall.height = 1080;
	lwall.width = 120;

	rwall.left = 1900;
	rwall.top = 0;
	rwall.height = 1080;
	rwall.width = 100;

	//draw
	dFloor.setSize(sf::Vector2f(1980, 100));
	dFloor.setPosition(sf::Vector2f(0,1060));
	dFloor.setFillColor(sf::Color(50,50,50));

	dCeiling.setSize(sf::Vector2f(1980, 120));
	dCeiling.setPosition(sf::Vector2f(0,-100));
	dCeiling.setFillColor(sf::Color(50, 50, 50));

	dLWall.setSize(sf::Vector2f(120, 1080));
	dLWall.setPosition(sf::Vector2f(-100,0));
	dLWall.setFillColor(sf::Color(50, 50, 50));

	dRWall.setSize(sf::Vector2f(100, 1080));
	dRWall.setPosition(sf::Vector2f(1900,0));
	dRWall.setFillColor(sf::Color(50, 50, 50));

}

void Map::draw(sf::RenderWindow& window) {

	window.draw(dFloor);
	window.draw(dCeiling);
	window.draw(dLWall);
	window.draw(dRWall);
}

float Map::checkCollision(sf::Vector2f coords, sf::FloatRect hitbox, float speed, Directions dir) {

	if (dir == LEFT) {
		hitbox.left -= speed;
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
	
}