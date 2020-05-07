#include "Icicle.h"

using namespace std;
using namespace cocos2d;

Icicle::Icicle(const std::string& filename, cocos2d::Node* _parent, cocos2d::Vec2 position, const BodyInfo& bodyInfo) :
	iMonster(filename, _parent, position, bodyInfo)
{

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
