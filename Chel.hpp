#pragma once

class Chel : public liveObject {
private:
	bool readyToJump;
	bool inAir;

	float holdingSpaceTimer;

	//for jump timer
	sf::Clock chelClock;
	sf::Texture chelTexture;

public:
	Chel(sf::Vector2f pos);
	bool isInAir();

	void getReadyToJump();
	void Jump();

	void updating(Map*, GameTime*);
	
};