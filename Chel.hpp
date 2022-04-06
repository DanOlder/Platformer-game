#pragma once

class Chel {
private:
	sf::Vector2f coords;
	sf::Vector2f speed;

	bool readyToJump;
	bool inAir;

	float holdingSpaceTimer;

	//for jump timer
	sf::Clock chelClock;

	//animation & hitbox
	Animation chelAnimation;
	sf::RectangleShape chelShape;
	sf::Texture chelTexture;

public:
	Chel();
	sf::Vector2f getCoords();

	void getReadyToJump();
	void Jump();

	void updating(Map*, GameTime*);
	void draw(sf::RenderWindow&);

	
};