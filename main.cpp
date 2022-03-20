#include <SFML/Graphics.hpp>
#include <iostream>

#include "Constants.hpp"
#include "Map.hpp"
#include "Chel.hpp"
#include "Game.hpp"



int main(){

	Game game;
	if (game.init() != 0) {
		return -1;
	}

	game.runGame();

	return 0;
}