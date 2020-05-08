#pragma once
#include "iSpawner.h"
#include "../monsters/shot.h"
class ShotSpawner : public iSpawner
{
public:
	ShotSpawner(cocos2d::Node* _parent, const  cocos2d::Sprite* player, int maxMonsterCount);
	void spawn() override;
	void removeShot(int shotTag);
private:
	void startSpawn() = delete;
	void addListeners() override;
private:
	const cocos2d::Sprite* playerSprite;
	cocos2d::PhysicsBody* playerSpriteBody;
	int playerHeight;
	bool canShot;
};

