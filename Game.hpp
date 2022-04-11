#pragma once

class Game {
private:
	sf::RenderWindow window;
	sf::View view;
	sf::Vector2f screenSize;

	sf::Texture bg;
	sf::RectangleShape bgShape;
	sf::Font font;

public:
	int init();
	void onResize();
	void runGame();
};
/*
class Object {
private:
	sf::Vector2f coords;
	sf::FloatRect hitbox;
	sf::RectangleShape chelShape;
	sf::Texture chelTexture;
public:
	Object();
	sf::Vector2f getCoords();
	sf::FloatRect getHitbox();
};

Object::Object() {

}

sf::Vector2f Object::getCoords() {

}

sf::FloatRect Object::getHitbox() {

}


class AnimatedObject : Object {
private:

public:

};*/