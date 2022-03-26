#pragma once

enum Directions {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

//window parameters
#define DEF_WIDTH 1920.f
#define DEF_HEIGHT 1080.f

//horizontal speed
#define CHEL_MAX_SPEED 15.f
#define CHEL_JUMP_SPEED 23.f

//acceleration
#define CHEL_ACC 0.5
#define G 0.5

//jumping
#define MAX_HOLDING_SPACE_TIME 0.5
#define MAX_JUMP_SPEED 25.f