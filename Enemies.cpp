#include "Hyperheader.hpp"

void Enemies::placeEnemies(int screenNum)
{
	switch (screenNum)
	{
	case 1: {
		enemyAppears<EnemyFly>(sf::Vector2f(8.f, -8.f));
		//enemyVec.push_back(temp);
		break;
	}
	case 2: {
		break;
	}
	case 3: {
		break;
	}
	default:
		break;
	}
}

void Enemies::removeEnemies()
{

}