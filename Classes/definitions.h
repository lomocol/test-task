#pragma once

#include "ImageManager.h"

#define PLAYER_IMAGE "player.png"
#define ICICLE_IMAGE "icicle.png"
#define ICICLE_SECOND_IMAGE "icicle2.png"
#define ICICLE_THIRD_IMAGE "icicle3.png"
#define SPIDER_IMAGE "spider.png"

#define NORMAL_GRAVITY Vec2(0,-50)
#define HEADER_HEIGHT 160


#define ICICLE_SPAWN_INTERVAL 1.0
#define ICICLE_APPEARANCE_TIME 3.0
#define ICICLE_COLUMN_RELEASE_TIME 0.5

#define SPIDER_SPAWN_INTERVAL 1.0
#define SPIDER_APPEARANCE_TIME 2.0
#define SPIDER_COLUMN_RELEASE_TIME 0.5

struct Range
{
	Range() noexcept {};
	Range(int _from, int _to) noexcept :from(_from), to(_to) {};
	int from = 0;
	int to = 0;
	bool conteins(int value) const noexcept { return value >= from && value <= to; };
};

#define PLAYER_MASK 1001
#define EDGE_MASK 1100
#define FOOTER_MASK 1101
#define CEILING_MASK 1102
#define ICICLE_MASK 100

