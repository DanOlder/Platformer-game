#pragma once

class Map {
private:
	sf::FloatRect floor;
	sf::FloatRect ceiling;
	sf::FloatRect lwall;
	sf::FloatRect rwall;

	//draw
	sf::RectangleShape dFloor;
	sf::RectangleShape dCeiling;
	sf::RectangleShape dLWall;
	sf::RectangleShape dRWall;
public:
	Map();
	void draw(sf::RenderWindow&);
	float checkCollision(sf::Vector2f, sf::FloatRect, float, Directions);
};