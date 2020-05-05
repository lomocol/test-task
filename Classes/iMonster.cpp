#include "iMonster.h"

using namespace cocos2d;

iMonster::iMonster(const std::string& filename, cocos2d::Node* _parent, cocos2d::Vec2 position, int mask) : 
	parent(_parent), health(100), sprite(nullptr)
{ 
	auto texture = ImageManager::instance().getTexture(filename);

	if (texture == nullptr)
		throw new std::exception("Image was not added to ImageManager");

	sprite = Sprite::createWithTexture(texture);

	sprite->setAnchorPoint(Point(0.5f, 1.0f));
	sprite->setPosition(position);

	auto spriteBody = PhysicsBody::createCircle(sprite->getContentSize().width / 2, PhysicsMaterial(0, 1, 0));
	spriteBody->setCollisionBitmask(mask);
	spriteBody->setContactTestBitmask(true);
	spriteBody->setDynamic(false);

	sprite->setPhysicsBody(spriteBody);
	parent->addChild(sprite);
}

void iMonster::changeHealth(float value)
{
	health += value;
	if (health <= 0)
		die();
}
