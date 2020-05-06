#include "iMonster.h"

using namespace cocos2d;

iMonster::iMonster(const std::string& filename, cocos2d::Node* _parent, cocos2d::Vec2 position, const BodyInfo bodyInfo) :
	parent(_parent), health(100), sprite(nullptr), tag(bodyInfo.tag)
{ 
	auto texture = ImageManager::instance().getTexture(filename);

	if (texture == nullptr)
		throw new std::exception("Image was not added to ImageManager");

	sprite = Sprite::createWithTexture(texture);

	sprite->setAnchorPoint(Point(0.5f, 1.0f));
	sprite->setPosition(position);

	auto spriteBody = PhysicsBody::createCircle(sprite->getContentSize().width / 2, PhysicsMaterial(0, 1, 0));
	spriteBody->setDynamic(false);
	setBodyInfo(spriteBody, bodyInfo);

	sprite->setPhysicsBody(spriteBody);
	
	parent->addChild(sprite);
}

void iMonster::changeHealth(float value)
{
	health += value;
	if (health <= 0)
		die();
}
