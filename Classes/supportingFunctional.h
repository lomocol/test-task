#pragma once
#include "cocos2d.h"

struct Range
{
	Range() noexcept {};
	Range(int _from, int _to) noexcept :from(_from), to(_to) {};
	int from = 0;
	int to = 0;
	bool conteins(int value) const noexcept { return value >= from && value <= to; };
};

struct BodyInfo
{
	int category = -1;
	int collisionMask = -1;
	int contactTest = -1;
	int tag = -1;
};

static void setBodyInfo(cocos2d::PhysicsBody* body, const BodyInfo& info)
{
	body->setCategoryBitmask(info.category);
	body->setCollisionBitmask(info.contactTest);
	body->setContactTestBitmask(info.contactTest);
	body->setTag(info.tag);
}