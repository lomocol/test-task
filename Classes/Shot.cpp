#include "Shot.h"

using namespace cocos2d;

Shot::Shot(cocos2d::Size size, cocos2d::Vec2 shotDirection, cocos2d::Node* _parent, cocos2d::Vec2 position, const BodyInfo bodyInfo) :
	iMonster(size,_parent,position,bodyInfo)
{
	appearance(SHOT_APPEARANCE_TIME);
	sprite->getPhysicsBody()->applyImpulse(shotDirection);
	health = SHOT_HEALTH;
}

void Shot::die()
{
	EventCustom event("shot_die_event");
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

void Shot::appearance(float time)
{

}
