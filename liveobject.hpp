#pragma once

class liveObject {
protected:
	sf::Vector2f coords;
	sf::Vector2f speed;
	sf::RectangleShape hitbox;
	Animation animation;
public:
	liveObject(sf::Vector2f pos);
	//in blocks
	void setPosition(sf::Vector2f);
	sf::Vector2f getCoords();
	sf::FloatRect getSpriteRect();
	void draw(sf::RenderWindow&);
};
