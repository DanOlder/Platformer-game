#pragma once
class GameTime{
private:
	sf::Clock clock;
public:
	GameTime();
	float deltaTime;

	float refresh();
};

