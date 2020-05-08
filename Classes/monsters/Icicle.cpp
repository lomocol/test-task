#include "Icicle.h"

using namespace std;
using namespace cocos2d;

Icicle::Icicle(const std::string& filename, cocos2d::Node* _parent, cocos2d::Vec2 position, const BodyInfo& bodyInfo) :
	iMonster(filename, _parent, position, bodyInfo)
{
	health = ICICLE_HEALTH;
}

void Icicle::appearance(float time)
{
	auto stageInterval = DelayTime::create(time / 3);

	auto secondStage = CallFunc::create([this]() {
		changeSize(ICICLE_SECOND_IMAGE);
		sprite->getPhysicsBody()->setDynamic(false);
		});
	auto thirdStage = CallFunc::create([this]() {changeSize(ICICLE_THIRD_IMAGE);});

	auto sequence = Sequence::create(stageInterval, secondStage, stageInterval, thirdStage, nullptr);
	parent->runAction(sequence);
}

void Icicle::die()
{
	sendNotifications();
}

void Icicle::sendNotifications()
{
	{
		EventCustom event("icicle_drop_bonus_event");
		Vec2* position = new Vec2(sprite->getPosition());
		event.setUserData(position);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}
	{
		EventCustom event("icicle_die_event");
		int* num = new int(tag - ICICLE_TAG);
		event.setUserData(num);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}
}

void Icicle::changeSize(const std::string& filename)
{
	auto texture = ImageManager::instance().getTexture(filename);

	auto newSize = texture->getContentSize();

	auto newSpriteBody = PhysicsBody::createCircle(newSize.width / 2, PhysicsMaterial(0, 1, 0));
	setBodyInfo(newSpriteBody, getBodyInfo(sprite->getPhysicsBody()));

	auto position = sprite->getPosition();

	sprite->removeFromParent();

	sprite = Sprite::createWithTexture(texture);
	sprite->setAnchorPoint(Point(0.5, 1));
	sprite->setPosition(position);
	sprite->setPhysicsBody(newSpriteBody);

	parent->addChild(sprite);
}
