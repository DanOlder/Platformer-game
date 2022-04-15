#pragma once

class Map {
private:
	std::vector<sf::RectangleShape> platforms;

public:
	Map();
	int screenCounter;


	void addPlatform(sf::Vector2f, sf::Vector2f, sf::Color);
	void lastPhaseInit();
	void updating(sf::FloatRect, sf::View*, sf::Vector2f);
	void draw(sf::RenderWindow&);
	bool checkCollision(sf::FloatRect, Directions, sf::Vector2f*);
	void parsingMap();

	template<typename T>
	void enemyAppears();
};

//template definition should be here in hpp
template<typename T>
inline void Map::enemyAppears()
{
	T enemy;

}
