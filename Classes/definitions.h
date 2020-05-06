#pragma once

#include "ImageManager.h"
#include "supportingFunctional.h"

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

#define SPIDER_SPAWN_INTERVAL 10.0
#define SPIDER_APPEARANCE_TIME 2.0
#define SPIDER_COLUMN_RELEASE_TIME 0.5

#define SPIDER_WEB_LENGHT_MIN 50
#define SPIDER_WEB_LENGHT_MAX 250
#define SPIDER_WEB_WIDTH_SCALE 0.33

// Ceinilg
#define CEILING_COLLISION_MASK 2
#define CEILING_CATEGORY 1
#define CEILING_TEST 2
#define CEILING_TAG 300
#define CEILING_BODY_INFO BodyInfo{CEILING_CATEGORY, CEILING_COLLISION_MASK, CEILING_TEST, CEILING_TAG}
// Edge
#define EDGE_COLLISION_MASK 2
#define EDGE_CATEGORY 1
#define EDGE_TEST 2
#define EDGE_TAG 200
#define EDGE_BODY_INFO BodyInfo{EDGE_CATEGORY, EDGE_COLLISION_MASK, EDGE_TEST, EDGE_TAG}
// Footer
#define FOOTER_COLLISION_MASK 2
#define FOOTER_CATEGORY 1
#define FOOTER_TEST 2
#define FOOTER_TAG 100
#define FOOTER_BODY_INFO BodyInfo{FOOTER_CATEGORY, FOOTER_COLLISION_MASK, FOOTER_TEST, FOOTER_TAG}
// Player
#define PLAYER_COLLISION_MASK 1
#define PLAYER_CATEGORY 3
#define PLAYER_TEST 1
#define PLAYER_TAG 1
#define PLAYER_BODY_INFO BodyInfo{PLAYER_CATEGORY, PLAYER_COLLISION_MASK, PLAYER_TEST, PLAYER_TAG}
// Icicle
#define ICICLE_COLLISION_MASK 1
#define ICICLE_CATEGORY 3
#define ICICLE_TEST 1
#define ICICLE_TAG 1100
#define ICICLE_BODY_INFO BodyInfo{ICICLE_CATEGORY, ICICLE_COLLISION_MASK, ICICLE_TEST, ICICLE_TAG}
// Spyder
#define SPIDER_COLLISION_MASK 1
#define SPIDER_CATEGORY 3
#define SPIDER_TEST 1
#define SPIDER_TAG 1200
#define SPIDER_BODY_INFO BodyInfo{SPIDER_CATEGORY, SPIDER_COLLISION_MASK, SPIDER_TEST, SPIDER_TAG}



