#pragma once

#define PLAYER_WIDTH 33
#define PLAYER_HEIGHT 33
#define PLAYER_SIZE Size(PLAYER_WIDTH,PLAYER_HEIGHT)
#define PLAYER_DAMAGE_COEFFICIENT 0.1	// The lower the coefficient, the less damage

#define ICICLE_WIDTH 35
#define ICICLE_HEIGHT 35
#define ICICLE_SIZE Size(ICICLE_WIDTH,ICICLE_HEIGHT)
#define ICICLE_PADDING 10

#define SPIDER_WIDTH 35
#define SPIDER_HEIGHT 35
#define SPIDER_SIZE Size(SPIDER_WIDTH,SPIDER_HEIGHT)
#define SPIDER_PADDING 4

#define COLUMN_COUNT 8

#define MAX_ICICLE_COUNT_FROM 4
#define MAX_ICICLE_COUNT_TO 20

#define MAX_SPIDER_COUNT_FROM 2
#define MAX_SPIDER_COUNT_TO 4

#define MAX_SHOT_COUNT_FROM 2
#define MAX_SHOT_COUNT_TO 6

#define DAMAGE_FROM_ICICLE 1.5
#define DAMAGE_FROM_SHOT 1
#define DAMAGE_FROM_SPIDER_SHOT 20
#define DAMAGE_FROM_SPIDER 20
#define DAMAGE_FROM_FRAGMENT 25

#define BONUS_SIZE Size(25,25)
#define BONUS_MAX_COUNT 4
#define BONUS_CHANCE 30		// BONUS_CHANCE out of 100 that will drop a bonus

