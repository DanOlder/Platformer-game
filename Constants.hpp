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

//block size
#define BLOCK_SIZE 60.f

//chel pos
#define CHEL_DEF_POS_X 23.f
#define CHEL_DEF_POS_Y -41.f

//size of hitbox/sprite
#define CHEL_HITBOX_WIDHT 80.f
#define CHEL_HITBOX_HEIGHT 80.f


//max speed (must be lower than BLOCK_SIZE)
#define CHEL_MAX_SPEED 12.f
#define MAX_FALLING_SPEED 30.0f

//acceleration
#define CHEL_ACC 0.7f
#define G 0.5f

//jumping
#define MAX_HOLDING_SPACE_TIME 0.5f
#define MAX_JUMP_SPEED 19.2f

#define BOUNCE_RATIO 0.3f