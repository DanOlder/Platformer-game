#include "Hyperheader.hpp"

Map::Map() {

	screenCounter = 0;

	//run Python script for refreshing map
	system("cd resources && python refreshMap.py");
	printf("refreshing done");
	parsingMap();

}

void Map::parsingMap() {

	sf::Color clr = sf::Color::Transparent;


	std::ifstream file("resources/map.txt");
	
	int x = 0;
	int y = 0;

	char block = 0;

	while (!file.eof()) {
		file >> block;

		if (block == 'D' || block == 'B' || block == 'W') {
			// for the last screen floor appearing
			if (y != 17 || x == 0 || x == 31) {
				addPlatform(sf::Vector2f(1.f, 1.f), sf::Vector2f(float(x), -72.f + float(y)), clr);
			}
		}

		x++;
		if (x > 31) {
			x = 0;
			y++;
		}
	}

}

void Map::addPlatform(sf::Vector2f size, sf::Vector2f position, sf::Color color) {

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
	addPlatform(sf::Vector2f(32.f, 1.f), sf::Vector2f(0.f, -55.f), sf::Color::Transparent);
}

void Map::updating(sf::FloatRect chelRect, sf::View* view, sf::Vector2f screenSize) {
	//watch top border of screen and bottom border of screen and then check if the character in this area

	float topBorder = 0 - screenCounter * DEF_HEIGHT;
	float bottomBorder = DEF_HEIGHT - screenCounter * DEF_HEIGHT;

	if ((screenCounter < 3 && chelRect.top + chelRect.height < topBorder)||(screenCounter == 3 && (chelRect.top + chelRect.height + BLOCK_SIZE < topBorder)) ) {
		sf::Vector2f oldCenter = view->getCenter();
		view->setCenter(oldCenter.x, oldCenter.y - DEF_HEIGHT);
		view->move(0.f, 0.f);
		screenCounter++;
		if (screenCounter == 4) {
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