#pragma once

class Map {
private:
	sf::FloatRect floor;
	sf::FloatRect ceiling;
	sf::FloatRect lwall;
	sf::FloatRect rwall;
	
	float lwall_x;
	float rwall_x;
	float floor_y;
	float ceiling_y;
public:
	Map();
	float checkCollision(sf::Vector2f, Directions);
};