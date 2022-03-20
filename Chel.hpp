#pragma once

class Chel {
private:
	float x;
	float y;
	sf::RectangleShape square;
public:
	Chel();
	void draw(sf::RenderWindow&);
	void updating();
};