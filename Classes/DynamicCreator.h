#pragma once

#include "cocos2d.h"
#include <queue>

struct CreationOrder
{
	cocos2d::Sprite* sprite;
	cocos2d::Vec2 position;
	cocos2d::Node * parent;
};


class DynamicCreator
{
public:
	static  DynamicCreator& instance()
	{
		static DynamicCreator creator;
		return creator;
	}
	void addCreationOrder(const CreationOrder order);
	void createSprites();
private:
	DynamicCreator() {};
private:
	std::queue<CreationOrder> orders;
};

