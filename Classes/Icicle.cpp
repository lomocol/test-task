#include "Icicle.h"

using namespace std;
using namespace cocos2d;

Icicle::Icicle(Vec2 position, int mask)
{
	sprite = Sprite::create("emoji/emoji9.png");
	auto spriteBody = PhysicsBody::createCircle(sprite->getContentSize().width / 2, PhysicsMaterial(0, 1, 0));
	spriteBody->setCollisionBitmask(mask);
	spriteBody->setContactTestBitmask(true);
	spriteBody->setDynamic(false);
	sprite->setPhysicsBody(spriteBody);
}

void Icicle::fall()
{
	auto stageInterval = DelayTime::create(1.4f);

	firstStage = CallFunc::create([this]() {sprite->setTexture("emoji/emoji8.png");});
	secondStage = CallFunc::create([this]() {sprite->setTexture("emoji/emoji7.png");});
	thirdStage = CallFunc::create([this]() {
		sprite->setTexture("emoji/emoji6.png");
		sprite->getPhysicsBody()->setDynamic(true);
		});

	auto growingUp = Sequence::create(firstStage, stageInterval, secondStage, stageInterval, thirdStage, nullptr);
	sprite->runAction(growingUp);
}

void Icicle::destroy()
{
	if (sprite == nullptr)
		return;

	auto pos = sprite->getPosition();
	auto parent = sprite->getParent();

	//auto emitter = ParticleFireworks::create();
	auto emitter = ParticleMeteor::create();
	emitter->setPosition(pos.x, pos.y - sprite->getContentSize().height / 2);
	emitter->setDuration(0.1f);
	parent->addChild(emitter, 5);

	parent->removeChild(sprite);
	//delete sprite;
	sprite = nullptr;
}
