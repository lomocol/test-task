#pragma once
#include "cocos2d.h"
#include "definitions.h"
#include "icicle.h"



class IcicleSpawner
{
public:
	IcicleSpawner(cocos2d::Node* _parent);
	void startSpawn();
private:
	void spawnIcicle();

private:
	cocos2d::Size arenaSize;
	cocos2d::Sprite* spawner;
	cocos2d::Node* parent;
	std::vector<Icicle*> icicles;
};