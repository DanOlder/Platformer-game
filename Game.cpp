#include <SFML/Graphics.hpp>
#include <string>

#include "Constants.hpp"
#include "GameTime.hpp"
#include "Animation.hpp"
#include "Map.hpp"
#include "Chel.hpp"
#include "Game.hpp"

/////////////////////////////////////
////////////////add://///////////////
//Make own sprite sheet//////////////
//Change textureRect calculation/////
//Add Time class/////////////////////+
//Platforms//////////////////////////
//Every platform collision checking//
//Map scrolling//////////////////////
//Shift acceleration/////////////////
/////////////////////////////////////
//Remove jumping while in the air////


int Game::init() {
	//Init window & view
	window.create(sf::VideoMode((int)DEF_WIDTH, (int)DEF_HEIGHT), "Hi there!", sf::Style::Close);

	view.setSize(DEF_WIDTH, DEF_HEIGHT);
	view.setCenter(DEF_WIDTH / 2.f, DEF_HEIGHT / 2.f);

	//Init FPS settings
	window.setFramerateLimit(60);

	//Disable key repeating
	window.setKeyRepeatEnabled(false);

	//Init background
	if (!bg.loadFromFile("resources/test_bg.jpg")) return -1;
	bgShape.setTexture(&bg);
	bgShape.setPosition(0.0f,0.0f);
	bgShape.setSize(sf::Vector2f(DEF_WIDTH,DEF_HEIGHT));

	//Init font
	if (!font.loadFromFile("resources/sansation.ttf")) return -1;

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

	GameTime gameTime;
	Chel chel;
	Map map;

	sf::Color bg_color = sf::Color(147, 163, 188);

	//start with lower resolution
	onResize(sf::Vector2f(1024.f, 576.f));

	//fps init
	float fps;

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
		chel.updating(&map, &gameTime);

		window.clear(bg_color);

		window.draw(bgShape);

		map.draw(window);
		chel.draw(window);

	



		//////////////FPS///////////////
		fps = 1.0f / gameTime.refresh();

		fps_text.setString(std::to_string((int)floor(fps)));
		window.draw(fps_text);
		////////////////////////////////



		window.display();
	}
}