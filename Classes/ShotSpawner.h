#pragma once
#include "iSpawner.h"
#include "shot.h"
class ShotSpawner : public iSpawner
{
public:
	ShotSpawner(cocos2d::Node* _parent, const  cocos2d::Sprite* player, int maxMonsterCount);
	void spawn() override;
private:
	void startSpawn() = delete;
private:
	const cocos2d::Sprite* playerSprite;
	cocos2d::PhysicsBody* playerSpriteBody;
	int playerHeight;
	bool canShot;
};

