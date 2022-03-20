#include <SFML/Graphics.hpp>
#include <iostream>

#include "Chel.hpp"
#include "Game.hpp"


int main(){

	Game game;
	game.init();
	game.runGame();

	return 0;
}