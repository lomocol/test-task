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

	auto secondStage = CallFunc::create([this]() {this->secondStage();});
	auto thirdStage = CallFunc::create([this]() {this->thirdStage();});

	auto sequence = Sequence::create(stageInterval, secondStage, stageInterval, thirdStage, nullptr);
	sprite->runAction(sequence);
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

void Icicle::split()
{
	{
		auto texture = ImageManager::instance().getTexture("fragment.png");
		if (texture == nullptr)
			return;
		auto fragment1 = Sprite::createWithTexture(texture);
		auto size = fragment1->getContentSize();
		auto spriteBody = PhysicsBody::createCircle(size.width / 2, PhysicsMaterial(0, 1, 0));
		spriteBody->setDynamic(false);
		setBodyInfo(spriteBody, FRAGMENT_BODY_INFO);
		fragment1->setPhysicsBody(spriteBody);
		auto pos = sprite->getPosition();
		pos.y += 40;
		fragment1->setPosition(pos);
		parent->addChild(fragment1);
	}
	
}

void Icicle::secondStage()
{
	auto texture = ImageManager::instance().getTexture("icicle2.png");
	auto newSize = texture->getContentSize();
	sprite->setTexture(texture);
	sprite->setContentSize(newSize);
	auto spriteBody = sprite->getPhysicsBody();
	spriteBody->createCircle(newSize.width / 2, PhysicsMaterial(0, 1, 0));
}

void Icicle::thirdStage()
{
	auto texture = ImageManager::instance().getTexture("icicle3.png");
	auto newSize = texture->getContentSize();
	sprite->setTexture(texture);
	sprite->setContentSize(newSize);
	auto spriteBody = sprite->getPhysicsBody();
	spriteBody->createCircle(newSize.width / 2, PhysicsMaterial(0, 1, 0));
	spriteBody->setDynamic(true);
}
