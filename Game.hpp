#pragma once

#define DEF_WIDTH 1920.f
#define DEF_HEIGHT 1080.f

class Game {
private:
	sf::RenderWindow window;
	sf::View view;
public:
	void init();
	void onResize(sf::Vector2f);
	void runGame();
};