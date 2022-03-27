#pragma once

class Chel {
private:
	sf::Vector2f coords;
	sf::FloatRect hitbox;
	float speed_x;
	float speed_y;

	bool readyToJump;
	bool inAir;

	float holdingSpaceTimer;

	//for jump timer
	sf::Clock chelClock;

	sf::RectangleShape square; //temp until the sprite is made

	//animation
	Animation chelAnimation;
	sf::RectangleShape chelShape;
	sf::Texture chelTexture;

public:
	Chel();
	sf::Vector2f getCoords();
	sf::FloatRect getHitbox();

	void getReadyToJump();
	void Jump();


	void updating(Map*, GameTime*);
	void draw(sf::RenderWindow&);

	
};