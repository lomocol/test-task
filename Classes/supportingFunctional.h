#pragma once
#include "cocos2d.h"


struct Range
{
	int from = 0;
	int to = 0;
	bool contains(int value) const noexcept { return value >= from && value <= to; };
};

struct BodyInfo
{
	int category;
	int collisionMask;
	int contactTest;
	int tag;
};

static void setBodyInfo(cocos2d::PhysicsBody* body, const BodyInfo& info)
{
	body->setCategoryBitmask(info.category);
	body->setCollisionBitmask(info.contactTest);
	body->setContactTestBitmask(info.contactTest);
	body->setTag(info.tag);
}

static BodyInfo getBodyInfo(cocos2d::PhysicsBody* body)
{
	return BodyInfo{
	body->getCategoryBitmask(),
	body->getCollisionBitmask(),
	body->getContactTestBitmask(),
	body->getTag()
	};
}
struct message {
	int tag;
	int columnNum;
	cocos2d::Vec2 position;
};