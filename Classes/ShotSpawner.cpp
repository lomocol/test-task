#include "ShotSpawner.h"

using namespace cocos2d;

ShotSpawner::ShotSpawner(cocos2d::Node* _parent, const cocos2d::Sprite* playerSprite, int maxMonsterCount) :
	iSpawner(_parent, maxMonsterCount), playerSprite(playerSprite)
{
	playerHeight = playerSprite->getContentSize().height;
	playerSpriteBody = playerSprite->getPhysicsBody();
	canShot = true;
}

void ShotSpawner::spawn()
{
	if (!canShot)
		return;

	int spriteNumber = getFreeMonsterNumber();

	if (spriteNumber != -1)
	{
		// Make shot
		Vec2 position = playerSprite->getPosition();
		position.y += playerHeight;

		BodyInfo bodyInfo = SHOT_BODY_INFO;
		bodyInfo.tag += spriteNumber;

		Vec2 direction = playerSpriteBody->getVelocity();
		direction.y = SHOT_VERTICAL_VELOCITY;

		Shot* shot = new Shot(SHOT_SIZE, direction, parent, position, bodyInfo);

		monsters[spriteNumber] = shot;
		canShot = false;

		// Waiting interval for the next shot
		auto delay = DelayTime::create(SHOT_SPAWN_INTERVAL);
		auto spawnCallFunc = CallFunc::create([this]() {canShot = true;});

		auto sequense = Sequence::create(delay, spawnCallFunc, nullptr);
		spawner->runAction(sequense);
	}
}
