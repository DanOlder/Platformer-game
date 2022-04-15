#include "Hyperheader.hpp"

int main(){

	Game game;
	if (game.init() != 0) {
		return -1;
	}

	game.runGame();

	return 0;
}