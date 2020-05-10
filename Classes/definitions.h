#pragma once

#include "ImageManager.h"
#include "supportingFunctional.h"
#include "dynamicCreator.h"

#define PLAYER_IMAGE "player.png"
#define PLAYER_DEAD_IMAGE "player_dead.png"

#define ICICLE_IMAGE "icicle.png"
#define ICICLE_SECOND_IMAGE "icicle2.png"
#define ICICLE_THIRD_IMAGE "icicle3.png"
#define SPIDER_IMAGE "spider.png"
#define SPIDER_DEAD_IMAGE "spider_dead.png"
#define FRAGMENT_IMAGE "fragment.png"

// bonus file names
#define BLOCK_IMAGE "bonus/block.png"
#define SHIELD_IMAGE "bonus/shield.png"
#define FIREBALL_IMAGE "bonus/fireball.png"
#define HEALTH_IMAGE "bonus/health.png"
#define PROTECTION_IMAGE "bonus/protection.png"

#define FOOTER_IMAGE "footer.jpg"
#define BACKGROUND_IMAGE "background.jpg"
#define CEILING_IMAGE "ceiling.png"
#define HEADER_IMAGE "header.jpg"

#define NORMAL_GRAVITY Vec2(0,-500)
#define HEADER_HEIGHT 120


#define CEILING_HEIGHT 45
#define FOOTER_HEIGHT 30


#define ICICLE_SPAWN_INTERVAL 2.0
#define ICICLE_APPEARANCE_TIME 3.0
#define ICICLE_COLUMN_RELEASE_TIME 0.5
#define ICICLE_DIE_EFFECT_DURATION 0.3
#define ICICLE_HEALTH 200

#define SHOT_SPAWN_INTERVAL 0.1
#define SHOT_APPEARANCE_TIME 0.1
#define SHOT_VERTICAL_VELOCITY 700
#define SHOT_SIZE Size(10,17)
#define SHOT_HEALTH 1

#define SPIDER_SHOT_SIZE Size(10,10)
#define SPIDER_SHOT_INTERVAL 2.0f
#define SPIDER_SHOT_POWER 17

#define SPIDER_SPAWN_INTERVAL 10.0
#define SPIDER_APPEARANCE_TIME 2.0
#define SPIDER_COLUMN_RELEASE_TIME 0.5
#define SPIDER_HEALTH 300
#define SPIDER_FALL_TIME 2.5
#define SPIDER_COLLAPSE_TIME 0.5

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
#define ICICLE_TAG_TO 1150
#define ICICLE_BODY_INFO BodyInfo{ICICLE_CATEGORY, ICICLE_COLLISION_MASK, ICICLE_TEST, ICICLE_TAG}
#define IS_ICICLE(tag) Range{ICICLE_TAG,ICICLE_TAG_TO}.contains(tag)
// Spyder
#define SPIDER_COLLISION_MASK 1
#define SPIDER_CATEGORY 3
#define SPIDER_TEST 1
#define SPIDER_TAG 1200
#define SPIDER_TAG_TO 1250
#define SPIDER_BODY_INFO BodyInfo{SPIDER_CATEGORY, SPIDER_COLLISION_MASK, SPIDER_TEST, SPIDER_TAG}
#define IS_SPIDER(tag) Range{SPIDER_TAG,SPIDER_TAG_TO}.contains(tag)
// Shot
#define SHOT_COLLISION_MASK 1
#define SHOT_CATEGORY 3
#define SHOT_TEST 1
#define SHOT_TAG 1300
#define SHOT_TAG_TO 1350
#define SHOT_BODY_INFO BodyInfo{SHOT_CATEGORY, SHOT_COLLISION_MASK, SHOT_TEST, SHOT_TAG}
#define IS_SHOT(tag) Range{SHOT_TAG,SHOT_TAG_TO}.contains(tag)
// Fragment
#define FRAGMENT_COLLISION_MASK 1
#define FRAGMENT_CATEGORY 3
#define FRAGMENT_TEST 1
#define FRAGMENT_TAG 1400
#define FRAGMENT_TAG_TO 1450
#define FRAGMENT_BODY_INFO BodyInfo{FRAGMENT_CATEGORY, FRAGMENT_COLLISION_MASK, FRAGMENT_TEST, FRAGMENT_TAG}
#define FRAGMENT_SIZE Size(10,10)	
#define FRAGMENT_LEFT cocos2d::Vec2(-88,150)	// fragment momentum
#define FRAGMENT_RIGHT cocos2d::Vec2(88,150)
#define FRAGMENT_UP cocos2d::Vec2(30,170)
#define IS_FRAGMENT(tag) Range{FRAGMENT_TAG,FRAGMENT_TAG_TO}.contains(tag)
// Bonus
#define BONUS_COLLISION_MASK 1
#define BONUS_CATEGORY 3
#define BONUS_TEST 1
#define BONUS_TAG 1500
#define BONUS_TAG_TO 1550
#define BONUS_BODY_INFO BodyInfo{BONUS_CATEGORY, BONUS_COLLISION_MASK, BONUS_TEST, BONUS_TAG}
#define IS_BONUS(tag) Range{BONUS_TAG,BONUS_TAG_TO}.contains(tag)

// Spider Shot
#define SPIDER_SHOT_COLLISION_MASK 1
#define SPIDER_SHOT_CATEGORY 3
#define SPIDER_SHOT_TEST 1
#define SPIDER_SHOT_TAG 1600
#define SPIDER_SHOT_TAG_TO 1650
#define SPIDER_SHOT_BODY_INFO BodyInfo{SPIDER_SHOT_CATEGORY, SPIDER_SHOT_COLLISION_MASK, SPIDER_SHOT_TEST, SPIDER_SHOT_TAG}
#define IS_SPIDER_SHOT(tag) Range{SPIDER_SHOT_TAG,SPIDER_SHOT_TAG_TO}.contains(tag)