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
	int interval = time / 3;

	auto secondStageAction = CallFunc::create([this, interval]() {secondStage(interval);});

	auto sequence = Sequence::create(DelayTime::create(interval), secondStageAction, nullptr);
	sprite->runAction(sequence);
}

void Icicle::die()
{
	sendNotifications();
}

void Icicle::secondStage(float interval)
{
	changeSize(ICICLE_SECOND_IMAGE);
	sprite->getPhysicsBody()->setDynamic(false);

	auto thirdStageAction = CallFunc::create([this]() {thirdStage();});

	auto sequence = Sequence::create(DelayTime::create(interval), thirdStageAction, nullptr);
	sprite->runAction(sequence);
};

void Icicle::thirdStage()
{
	changeSize(ICICLE_THIRD_IMAGE);
}

void Icicle::sendNotifications()
{
	{
		EventCustom event("icicle_drop_bonus_event");
		auto topPosition = sprite->getPosition();	// sprite position with anchorPoint(0.5,1)
		Vec2* position = new Vec2(topPosition.x, topPosition.y - sprite->getContentSize().height); // sprite position with anchorPoint(0.5,0)
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
