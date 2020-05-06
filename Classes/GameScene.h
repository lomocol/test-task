#pragma once

#include "cocos2d.h"
#include "definitions.h"
#include "Header.h"
#include "Player.h"
#include "icicleSpawner.h"
#include "spiderSpawner.h"

class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameScene);

	bool onContactBegin(cocos2d::PhysicsContact& contact);
private:
	void setPhysicsWorld(cocos2d::PhysicsWorld* _world) { world = _world; };
	void createHeader();
	void createGameSurface();
	void createPlayer();
	void addListeners();
	void startIcicleSpawn();
	void startSpiderSpawn();
	void initManagers();
	void contactWithPlayer(int contactorTag);
	void contactWithIcicle(int icicleTag, int contactorTag);
	void contactWithSpider(int spiderTag, int contactorTag);
private:
	IcicleSpawner* icicleSpawner;
	SpiderSpawner* spiderSpawner;
	ColumnManager* columnManager;
	Header* header;
	Player* player;
	cocos2d::PhysicsWorld* world;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Node* arena;


};


