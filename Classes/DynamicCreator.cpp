#include "DynamicCreator.h"

using namespace std;
using namespace cocos2d;

void DynamicCreator::addCreationOrder(const CreationOrder order)
{
	order.sprite->retain();
	orders.push(order);
}

void DynamicCreator::createSprites()
{
	int ordersCount = orders.size();
	if (ordersCount != 0)
	{
		for (int i = 0; i < ordersCount; i++)
		{
			const CreationOrder& order = orders.front();
			auto sprite = order.sprite;
			sprite->setPosition(order.position);
			order.parent->addChild(sprite);
			sprite->release();

			orders.pop();
		}
	}
}

