#pragma once
class EnemyFly : liveObject{
private:
	sf::Texture flyTexture;
public:
	EnemyFly(sf::Vector2f pos);
	void updating(Map*, GameTime*);
};

