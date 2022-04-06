#pragma once

class Map {
private:
	std::vector<sf::RectangleShape> platforms;

public:
	Map();
	void addPlatform(sf::Vector2f, sf::Vector2f, sf::Color);
	void draw(sf::RenderWindow&);
	bool checkCollision(sf::FloatRect, Directions, sf::Vector2f*);
};