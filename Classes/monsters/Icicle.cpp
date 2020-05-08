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
	
	EventCustom event("icicle_die_event");
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	if (sprite == nullptr)
		return;

	float duration = ICICLE_DIE_EFFECT_DURATION;

	auto pos = sprite->getPosition();
	auto parent = sprite->getParent();

	auto emitter = ParticleMeteor::create();
	emitter->setPosition(pos.x, pos.y - sprite->getContentSize().height);
	emitter->setDuration(duration);
	parent->addChild(emitter);

	auto emitterRemovingSequence = Sequence::create(DelayTime::create(duration),
		CallFunc::create([emitter]() {emitter->removeFromParent();})
		, nullptr);

	emitter->runAction(emitterRemovingSequence);
	
	sprite->removeFromParent();

	
}

void Icicle::changeSize(const std::string& filename)
{
	auto texture = ImageManager::instance().getTexture(filename);

	auto newSize = texture->getContentSize();

	auto newSpriteBody = PhysicsBody::createCircle(newSize.width / 2, PhysicsMaterial(0, 1, 0));
	setBodyInfo(newSpriteBody, getBodyInfo(sprite->getPhysicsBody()));

	auto pos = sprite->getPosition();

	sprite->removeFromParent();

	sprite = Sprite::createWithTexture(texture);
	sprite->setAnchorPoint(Point(0.5, 1));
	sprite->setPosition(pos);
	sprite->setPhysicsBody(newSpriteBody);

	parent->addChild(sprite);
}
