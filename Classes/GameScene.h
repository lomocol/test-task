#pragma once

#include "cocos2d.h"
#include "definitions.h"
#include "Header.h"
#include "monsters/Player.h"
#include "spawners/BonusSpawner.h"
#include "spawners/icicleSpawner.h"
#include "spawners/spiderSpawner.h"


class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameScene);

	void update(float dt);
	bool onContactBegin(cocos2d::PhysicsContact& contact);
private:
	void setPhysicsWorld(cocos2d::PhysicsWorld* _world) noexcept { world = _world; };
	void createHeader();
	void createGameSurface();
	void createPlayer();
	void addListeners();
	void startIcicleSpawn();
	void startSpiderSpawn();
	void initManagers();

	void contactWithPlayer(int contactorTag, cocos2d::PhysicsBody* contactorBody);
	void contactWithIcicle(int icicleTag, int contactorTag);
	void contactWithSpider(int spiderTag, int contactorTag);
	bool contactWithShot(int shotTag, int contactorTag);
	void contactWithFragment(cocos2d::PhysicsBody* fragmentBody, int contactorTag);
	bool contactWithBonus(int bonusTag, int contactorTag);
	void contactWithSpiderShot(cocos2d::PhysicsBody* spiderShotBody, int contactorTag);
private:
	IcicleSpawner* icicleSpawner;
	SpiderSpawner* spiderSpawner;
	BonusSpawner* bonusSpawner;
	ShotSpawner* shotSpawner;
	ColumnManager* columnManager;
	Header* header;
	Player* player;
	cocos2d::PhysicsWorld* world;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Node* arena;
};


