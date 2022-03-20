#pragma once

class Chel {
private:

	sf::Vector2f coords;
	sf::RectangleShape square;
public:
	Chel();
	sf::Vector2f getCoords();
	void updating(Map*);
	void draw(sf::RenderWindow&);
};