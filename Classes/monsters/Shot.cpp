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
	
	if (sprite == nullptr)
		return;

	EventCustom event("shot_die_event");
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);

	float duration = ICICLE_DIE_EFFECT_DURATION;

	auto parent = sprite->getParent();

	auto emitter = ParticleMeteor::create();
	emitter->setPosition(sprite->getPosition());
	emitter->setDuration(duration);
	emitter->setStartColor(Color4F::GRAY);
	parent->addChild(emitter);

	auto emitterRemovingSequence = Sequence::create(DelayTime::create(duration),
		CallFunc::create([emitter]() {emitter->removeFromParent();})
		, nullptr);

	emitter->runAction(emitterRemovingSequence);
}

void Shot::appearance(float time)
{

}
