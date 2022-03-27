#pragma once

class Animation {
private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float totalTime;
	float switchTime;
public:
	Animation();
	sf::IntRect spriteRect;

	void init(sf::Texture*, sf::Vector2u, float);
	void update(int, float);
};

