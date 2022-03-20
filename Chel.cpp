#include <SFML/Graphics.hpp>

#include "Chel.hpp"
#include "Game.hpp"


Chel::Chel() {
	x = 100;
	y = 100;
	square.setSize((sf::Vector2f(50.f, 50.f)));
}

void Chel::draw(sf::RenderWindow& window) {
	square.setPosition(x, y);
	window.draw(square);
}

void Chel::updating() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		x+=4;
	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
		x-=4;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up))) {
		y-=4;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down))) {
		y+=4;
	}
}