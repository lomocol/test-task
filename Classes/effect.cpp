#include "effect.h"

using namespace std;
using namespace cocos2d;


void EffectMaker::dropDefaultEfffect(cocos2d::Node* parent, cocos2d::Vec2 position, EffectType type, float duration)
{
	ParticleSystemQuad* emitter = nullptr;
		
	switch (type)
	{
	case Fire:
			emitter = ParticleMeteor::create();
		break;
	case Space:
			emitter = ParticleFire::create();
		break;
	default:
		throw new exception("Unknown EffectType");
		break;
	}

	emitter->setPosition(position);
	emitter->setDuration(duration);
	parent->addChild(emitter);

	/*auto emitterRemovingSequence = Sequence::create(DelayTime::create(duration),
		CallFunc::create([emitter]() {emitter->removeFromParent();})
		, nullptr);

	emitter->runAction(emitterRemovingSequence);*/

	auto removeFunc = CallFunc::create([emitter]() {emitter->removeFromParent();});
	auto delay = DelayTime::create(duration);
	auto removeSequence = Sequence::create(delay, removeFunc,nullptr);
	parent->runAction(removeSequence);
}

void EffectMaker::dropFragments(cocos2d::Node* parent, cocos2d::Vec2 position)
{

	// LEFT
	{
		auto sprite = createFragment(parent, position);
		sprite->getPhysicsBody()->applyImpulse(FRAGMENT_LEFT);
	}
	// UP
	{
		auto sprite = createFragment(parent, position);
		sprite->getPhysicsBody()->applyImpulse(FRAGMENT_UP);
	}
	// RIGHT
	{
		auto sprite = createFragment(parent,position);
		sprite->getPhysicsBody()->applyImpulse(FRAGMENT_RIGHT);
	}
}

cocos2d::Sprite* EffectMaker::createFragment(cocos2d::Node* parent, cocos2d::Vec2 position)
{
	auto texture = ImageManager::instance().getTexture(FRAGMENT_IMAGE);
	auto sprite = Sprite::createWithTexture(texture);
	sprite->setPosition(position);

	auto spriteBody = PhysicsBody::createCircle(sprite->getContentSize().width / 2, PhysicsMaterial(0, 1, 0));
	setBodyInfo(spriteBody, FRAGMENT_BODY_INFO);

	sprite->setPhysicsBody(spriteBody);
	parent->addChild(sprite);

	return sprite;
}
