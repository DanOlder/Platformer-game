#include "Hyperheader.hpp"

//////////////////////////////////////////////////////////////////////////
//----------------------------add:--------------------------------------//
//----------Sort headers------------------------------------------------//
//----------Make my own sprite sheet------------------------------------//
//----------Change textureRect calculation------------------------------//
//----------Optimize collitions check (threads or only near block)------//
//																		//
//----------Shift acceleration???---------------------------------------//
//----------object template---------------------------------------------//
//																		//
//----draw and check collisions only if object is on the screen---------//
//--------or on the adjoined borders of other screens-------------------//
//------------------(also it'd be nice to place objects-----------------//
//----------------------from different screens to different vectors)----//
// 
//+++hyperheader added
//+++parent class for all animated objects added
//////////////////////////////////////////////////////////////////////////

int Game::init() {
	//Init window & view
	screenSize.x = DEF_WIDTH;
	screenSize.y = DEF_HEIGHT;

	window.create(sf::VideoMode((unsigned int)screenSize.x, (unsigned int)screenSize.y), "Hi there!", sf::Style::Close);

	view.setSize(screenSize.x, screenSize.y);
	view.setCenter(screenSize.x / 2.f, screenSize.y / 2.f);

	//Init FPS settings
	window.setFramerateLimit(60);

	//Disable key repeating
	window.setKeyRepeatEnabled(false);

	//Init background
	if (!bg.loadFromFile("resources/game bg.png")) return -1;
	bgShape.setTexture(&bg);
	bgShape.setPosition(0.0f, -screenSize.y * 4.f);
	bgShape.setSize(sf::Vector2f(screenSize.x, screenSize.y*5));

	//Init font
	if (!font.loadFromFile("resources/sansation.ttf")) return -1;

	enemySheet = 0;

	return 0;
}

void Game::onResize() {

	// Apply possible size changes
	window.setSize((sf::Vector2u)screenSize);

}

void Game::runGame() {

	//start with lower resolution
	screenSize = sf::Vector2f(1024.f, 576.f);
	onResize();

	//fps init
	float fps;

	sf::Text fps_text;
	fps_text.setFont(font);
	fps_text.setFillColor(sf::Color(0, 0, 0));


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
					screenSize = sf::Vector2f(1024.f, 576.f);
					onResize();
					break;
				}
				else if (event.key.code == sf::Keyboard::Num2)
				{
					screenSize = sf::Vector2f(1280.f, 720.f);
					onResize();
					break;
				}
				else if (event.key.code == sf::Keyboard::Num3)
				{
					screenSize = sf::Vector2f(1600.f, 900.f);
					onResize();
					break;
				}
				else if (event.key.code == sf::Keyboard::Num4)
				{
					screenSize = sf::Vector2f(1760.f, 990.f);
					onResize();
					break;
				}
				else if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
					return;
				}

				//jump
				else if (event.key.code == sf::Keyboard::Space && !chel.isInAir())
				{
					chel.getReadyToJump();
					break;
				}

				//debug
				else if (event.key.code == sf::Keyboard::W)
				{
					sf::Vector2f oldCenter = view.getCenter();
					view.setCenter(oldCenter.x, oldCenter.y - DEF_HEIGHT);
					view.move(0.f, 0.f);
				}
				else if (event.key.code == sf::Keyboard::S)
				{
					sf::Vector2f oldCenter = view.getCenter();
					view.setCenter(oldCenter.x, oldCenter.y + DEF_HEIGHT);
					view.move(0.f, 0.f);
				}
				
			}
			case sf::Event::KeyReleased: {

				//jump
				if (event.key.code == sf::Keyboard::Space && !chel.isInAir())
				{
					chel.Jump();
					break;
				}
			}
			}
		}

		chel.updating(&map, &gameTime);

		//responsible for view change
		map.updating(chel.getSpriteRect(), &view, screenSize);

		int screenCounter = map.screenCounter;
		if (screenCounter != enemySheet) {
			enemies.removeEnemies();
			enemies.placeEnemies(screenCounter);
			enemySheet = screenCounter;
		}

		window.setView(view);

		window.clear();
		window.draw(bgShape);

		map.draw(window);


		//for (int i = 0; i < 1 && enemies.enemyVec.size() != 0; i++) {
		//	enemies.enemyVec[i]->updating(&map, &gameTime);
		//	enemies.enemyVec[i]->draw(window);
		//}

		chel.draw(window);

	



		//////////////FPS///////////////
		fps = 1.0f / gameTime.refresh();

		fps_text.setPosition(20, map.screenCounter * -1080.f + 20);
		fps_text.setString(std::to_string((int)floor(fps)));
		window.draw(fps_text);
		////////////////////////////////



		window.display();
	}
}
