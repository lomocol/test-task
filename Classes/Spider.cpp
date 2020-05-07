#include "Spider.h"

using namespace std;
using namespace cocos2d;
using namespace ui;

Spider::Spider(const std::string& filename, cocos2d::Node* _parent, cocos2d::Vec2 position, const BodyInfo & bodyInfo) :
	iMonster(filename,_parent, position, bodyInfo)
{
	health = SPIDER_HEALTH;
}

void Spider::die()
{
	EventCustom event("spider_die_event");
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);

	if (sprite == nullptr)
		return;

	float duration = ICICLE_DIE_EFFECT_DURATION;

	auto pos = sprite->getPosition();
	auto parent = sprite->getParent();

	auto emitter = ParticleMeteor::create();
	emitter->setPosition(pos.x, pos.y - sprite->getContentSize().height / 2);
	emitter->setDuration(duration);
	parent->addChild(emitter);

	auto emitterRemovingSequence = Sequence::create(DelayTime::create(duration),
		CallFunc::create([emitter]() {emitter->removeFromParent();})
		, nullptr);

	emitter->runAction(emitterRemovingSequence);

	sprite->removeFromParent();
}

void Spider::appearance(float time)
{
	int webLenght = rand() % (SPIDER_WEB_LENGHT_MAX - SPIDER_WEB_LENGHT_MIN) + SPIDER_WEB_LENGHT_MIN;

	LoadingBar * web = LoadingBar::create("bar.png");

	web->setScale(webLenght / web->getContentSize().width, SPIDER_WEB_WIDTH_SCALE);
	web->setDirection(LoadingBar::Direction::LEFT);
	web->setAnchorPoint(Point(0,0.5));
	web->setRotation(90.0);
	web->setPosition(sprite->getPosition());

	parent->addChild(web);
	web->runAction(ProgressTo::create(SPIDER_APPEARANCE_TIME, 100));

	auto spiderMoveDown = MoveBy::create(SPIDER_APPEARANCE_TIME,Vec2(0,-webLenght));
	sprite->runAction(spiderMoveDown);

	auto webRemove = CallFunc::create([web]() {web->removeFromParent();});
	auto sequence = Sequence::create(DelayTime::create(SPIDER_APPEARANCE_TIME), webRemove,nullptr);
	parent->runAction(sequence);
	
}
