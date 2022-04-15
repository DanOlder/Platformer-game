#include "Hyperheader.hpp"

GameTime::GameTime(){

	deltaTime = 0.0f;
}

float GameTime::refresh() {

	deltaTime = clock.restart().asSeconds();
	return deltaTime;
}
