#pragma once
#include "cocos2d.h"
#include "definitions.h"
#include "settings.h"
#include "ColumnManager.h"
#include "icicle.h"
#include <array>



class SpawnManager
{
public:
	SpawnManager(cocos2d::Node* _parent);
	void startIcicleSpawn();
private:
	void renderTextures();
	void spawnIcicle();
	int getFreeSpriteNumber();
private:
	ColumnManager* columnManager;
	cocos2d::Size arenaSize;
	cocos2d::Sprite* isicleSpawner;
	cocos2d::Sprite* monsterSpawner;
	cocos2d::Node* parent;
	std::vector<Icicle*> icicles;

	float growingUpTime;
	size_t columnWidth;
	size_t icicleWidth;
	int columnCount;
	//std::vector<Icicle*> monsters;
};