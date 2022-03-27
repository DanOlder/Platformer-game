#pragma once

class Game {
private:
	sf::RenderWindow window;
	sf::View view;

	sf::Texture bg;
	sf::RectangleShape bgShape;
	sf::Font font;

public:
	int init();
	void onResize(sf::Vector2f);
	void runGame();
};