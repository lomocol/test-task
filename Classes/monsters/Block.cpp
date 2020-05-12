#include "Block.h"

using namespace std;
using namespace cocos2d;

static const int blockHealth = 200;

Block::Block(cocos2d::Texture2D* texture, cocos2d::Node* _parent, cocos2d::Vec2 position, const BodyInfo& bodyInfo) :
	iMonster(texture->getContentSize(), _parent, position, bodyInfo)
{
	sprite->setAnchorPoint(Point(0.5f, 0.0f));
	sprite->getPhysicsBody()->setDynamic(false);
	sprite->setTexture(texture);
	health = blockHealth;
}

void Block::die()
{
	// two explosions when block is dead
	Size spriteSize = sprite->getContentSize();
	Vec2 spritePosition = sprite->getPosition();
	Vec2 oneEnd = { spritePosition.x - spriteSize.width / 2, spritePosition.y + spriteSize.height / 2 };
	Vec2 twoEnd = { spritePosition.x + spriteSize.width / 2, spritePosition.y + spriteSize.height / 2 };
	EffectMaker::instance().dropDefaultEfffect(parent, oneEnd, EffectType::Fire, 0.5f);
	EffectMaker::instance().dropDefaultEfffect(parent, twoEnd, EffectType::Fire, 0.5f);

	sendNotifications();
}

void Block::sendNotifications()
{
	EventCustom event("block_die_event");
	int* num = new int(tag - BLOCK_TAG);
	event.setUserData(num);
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}
