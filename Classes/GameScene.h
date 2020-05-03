#pragma once

#include "cocos2d.h"
#include "definitions.h"

class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameScene);

private:
	void setPhysicsWorld(cocos2d::PhysicsWorld* _world) { world = _world; };
	void createHeader();
	void createGameSurface();

private:
	cocos2d::PhysicsWorld* world;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Node* arena;


};


