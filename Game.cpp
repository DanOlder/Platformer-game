#include <SFML/Graphics.hpp>

#include "Chel.hpp"
#include "Game.hpp"


void Game::init() {
	//Init window & view
	window.create(sf::VideoMode((int)DEF_WIDTH, (int)DEF_HEIGHT), "Hi there!", sf::Style::Close);

	view.setSize(DEF_WIDTH, DEF_HEIGHT);
	view.setCenter(DEF_WIDTH / 2.f, DEF_HEIGHT / 2.f);

	//Init FPS settings
	window.setFramerateLimit(60);
}

void Game::onResize(sf::Vector2f size) {

	// Apply possible size changes
	window.setSize((sf::Vector2u)size);

	// Reset grid view
	view.setCenter(size.x / 2.f, size.y / 2.f);
	view.setSize(size);
}

void Game::runGame() {

	sf::Event event;
	Chel chel;

	//start with lower resolution
	onResize(sf::Vector2f(1024.f, 576.f));


	while (window.isOpen())
	{

		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed: {
				window.close();
				return;
			}

			case sf::Event::KeyPressed: {

				if (event.key.code == sf::Keyboard::Num1)
				{
					onResize(sf::Vector2f(1024.f, 576.f));
				}
				if (event.key.code == sf::Keyboard::Num2)
				{
					onResize(sf::Vector2f(1280.f, 720.f));
				}
				if (event.key.code == sf::Keyboard::Num3)
				{
					onResize(sf::Vector2f(1600.f, 900.f));
				}
				if (event.key.code == sf::Keyboard::Num4)
				{
					onResize(sf::Vector2f(1920.f, 1080.f));
				}
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
					return;
				}
			}
			}
		}
		chel.updating();

		window.clear();

		chel.draw(window);

		window.display();
	}
}