#include <SFML/Graphics.hpp>
#include <string>

#include "Constants.hpp"
#include "Map.hpp"
#include "Chel.hpp"
#include "Game.hpp"

/////////////////////////////////////
////////////////add://///////////////
//Shift acceleration/////////////////
//Every platform collision checking//
/////////////////////////////////////


int Game::init() {
	//Init window & view
	window.create(sf::VideoMode((int)DEF_WIDTH, (int)DEF_HEIGHT), "Hi there!", sf::Style::Close);

	view.setSize(DEF_WIDTH, DEF_HEIGHT);
	view.setCenter(DEF_WIDTH / 2.f, DEF_HEIGHT / 2.f);

	//Init FPS settings
	window.setFramerateLimit(60);

	//Disable key repeating
	window.setKeyRepeatEnabled(false);

	//Init font
	if (!font.loadFromFile("resources/sansation.ttf"))
	{
		return -1;
	}

	return 0;
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
	Map map;

	sf::Color bg_color = sf::Color(147, 163, 188);

	//start with lower resolution
	onResize(sf::Vector2f(1024.f, 576.f));

	//fps init
	float fps;
	sf::Clock clock = sf::Clock::Clock();
	sf::Time previousTime = clock.getElapsedTime();
	sf::Time currentTime;
	sf::Text fps_text;
	fps_text.setFont(font);
	fps_text.setFillColor(sf::Color(100, 0, 0));
	fps_text.setPosition(20, 20);


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

				//game settings
				if (event.key.code == sf::Keyboard::Num1)
				{
					onResize(sf::Vector2f(1024.f, 576.f));
					break;
				}
				else if (event.key.code == sf::Keyboard::Num2)
				{
					onResize(sf::Vector2f(1280.f, 720.f));
					break;
				}
				else if (event.key.code == sf::Keyboard::Num3)
				{
					onResize(sf::Vector2f(1600.f, 900.f));
					break;
				}
				else if (event.key.code == sf::Keyboard::Num4)
				{
					onResize(sf::Vector2f(1760.f, 990.f));
					break;
				}
				else if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
					return;
				}

				//jump
				else if (event.key.code == sf::Keyboard::Space)
				{
					chel.getReadyToJump();
					break;
				}
				


			}
			case sf::Event::KeyReleased: {

				//jump
				if (event.key.code == sf::Keyboard::Space)
				{
					chel.Jump();
					break;
				}
			}
			}
		}
		chel.updating(&map);

		window.clear(bg_color);


		map.draw(window);
		chel.draw(window);

	



		//////////////FPS///////////////
		currentTime = clock.getElapsedTime();
		fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds()); // the asSeconds returns a float

		fps_text.setString(std::to_string((int)floor(fps)));
		window.draw(fps_text);

		previousTime = currentTime;
		////////////////////////////////



		window.display();
	}
}