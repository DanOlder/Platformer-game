#pragma once
class Enemies
{
public:
	std::vector<EnemyFly*> enemyVec;

	void placeEnemies(int);
	void removeEnemies();

	template<typename T>
	T* enemyAppears(sf::Vector2f);
	template<typename T>
	T* enemyAppears(sf::Vector2f pos, sf::Vector2f speed);
};

//template definition should be here in hpp
template<typename T>
inline T* Enemies::enemyAppears(sf::Vector2f pos)
{
	T enemy(pos);

	enemyVec.push_back(&enemy);

	return &enemy;
}
template<typename T>
inline T* Enemies::enemyAppears(sf::Vector2f pos, sf::Vector2f speed)
{
	T enemy(pos);

	enemy.speed.x = speed.x;
	enemy.speed.y = speed.y;

	enemyVec.push_back(&enemy);

	return &enemy;
}

