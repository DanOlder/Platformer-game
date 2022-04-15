#pragma once

class Game {
private:

	GameTime gameTime;
	Chel chel = Chel(sf::Vector2f(CHEL_DEF_POS_X, CHEL_DEF_POS_Y));
	Map map;

	sf::Event event;

	sf::RenderWindow window;
	sf::View view;
	sf::Vector2f screenSize;

	sf::Texture bg;
	sf::RectangleShape bgShape;
	sf::Font font;

public:
	int init();
	void onResize();
	void runGame();
};