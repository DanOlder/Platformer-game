#include <SFML/Graphics.hpp>

#include "Animation.hpp"

Animation::Animation(){

}

void Animation::init(sf::Texture* texture, sf::Vector2u imageCount, float switchTime) {

	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;

	spriteRect.width = texture->getSize().x / float(imageCount.x);
	spriteRect.height = texture->getSize().y / float(imageCount.y);
}

void Animation::update(int row, float deltaTime)
{
	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime) {

		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= imageCount.x) {
			currentImage.x = 0;
		}
	}
	spriteRect.left = currentImage.x * spriteRect.width;
	spriteRect.top = currentImage.y * spriteRect.height;
}
