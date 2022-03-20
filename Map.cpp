#include <SFML/Graphics.hpp>

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
	

	lwall_x = 20;
	rwall_x = 1900;
	floor_y = 1060;
	ceiling_y = 20;

}

float Map::checkCollision(sf::Vector2f coords, Directions dir) {

	if (dir == LEFT) {
		if (lwall.contains(coords.x - CHEL_MAX_SPEED, coords.y)) {
			return coords.x - lwall_x;
		}
		else return CHEL_MAX_SPEED+1;
	}
	if (dir == RIGHT) {
		if (rwall.contains(coords.x + 50 + CHEL_MAX_SPEED, coords.y)) {
			return rwall_x - (coords.x+50);
		}
		else return CHEL_MAX_SPEED + 1;
	}
	if (dir == UP) {
		if (ceiling.contains(coords.x, coords.y - CHEL_MAX_SPEED)) {
			return coords.y - ceiling_y;
		}
		else return CHEL_MAX_SPEED + 1;
	}
	if (dir == DOWN) {
		if (floor.contains(coords.x, coords.y + 50 + CHEL_MAX_SPEED)) {
			return floor_y - (coords.y + 50);
		}
		else return CHEL_MAX_SPEED + 1;
	}
	
}