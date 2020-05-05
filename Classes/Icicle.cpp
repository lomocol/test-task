#include "Icicle.h"

using namespace std;
using namespace cocos2d;

Icicle::Icicle(const std::string& filename,cocos2d::Node* _parent, cocos2d::Vec2 position, int mask) :
	iMonster(filename,_parent, position, mask)
{
	
}

void Icicle::appearance(float time)
{
	auto stageInterval = DelayTime::create(time / 3);

	auto firstStage = CallFunc::create([this]() {this->firstStage();});
	auto secondStage = CallFunc::create([this]() {this->secondStage();});
	auto thirdStage = CallFunc::create([this]() {this->thirdStage();});

	auto sequence = Sequence::create(firstStage, stageInterval, secondStage, stageInterval, thirdStage, nullptr);
	sprite->runAction(sequence);
}

void Icicle::die()
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

void Icicle::firstStage()
{
	auto texture = ImageManager::instance().getTexture("icicle.png");
	auto newSize = texture->getContentSize();
	sprite->setTexture(texture);
	sprite->setContentSize(newSize);
	auto spriteBody = PhysicsBody::createCircle(newSize.width / 2, PhysicsMaterial(0, 1, 0));
	spriteBody->setDynamic(false);
	sprite->setPhysicsBody(spriteBody);
}

void Icicle::secondStage()
{
	auto texture = ImageManager::instance().getTexture("icicle2.png");
	auto newSize = texture->getContentSize();
	sprite->setTexture(texture);
	sprite->setContentSize(newSize);
	auto spriteBody = PhysicsBody::createCircle(newSize.width / 2, PhysicsMaterial(0, 1, 0));
	spriteBody->setDynamic(false);
	sprite->setPhysicsBody(spriteBody);
}

void Icicle::thirdStage()
{
	auto texture = ImageManager::instance().getTexture("icicle3.png");
	auto newSize = texture->getContentSize();
	sprite->setTexture(texture);
	sprite->setContentSize(newSize);
	auto spriteBody = PhysicsBody::createCircle(newSize.width / 2, PhysicsMaterial(0, 1, 0));
	spriteBody->setDynamic(true);
	sprite->setPhysicsBody(spriteBody);
}
