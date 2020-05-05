#pragma once
#include "cocos2d.h"
#include "definitions.h"
#include "settings.h"
#include "ColumnManager.h"
#include "iMonster.h"
#include <vector>
class iSpawner
{
public:
	iSpawner(cocos2d::Node* _parent, ColumnManager* columnManager, int maxMonsterCount);
	virtual void startSpawn() = 0;
protected:
	virtual void spawn() = 0;
	int getFreeMonsterNumber() const;
protected:
	ColumnManager* columnManager;
	cocos2d::Node* parent;
	std::vector<iMonster*> monsters;
	cocos2d::Sprite* spawner;
	float spawnYPosition;
	int maxMonsterCount;
	float spawnInterval = -1;
	float appearanceTime = -1;
	float columnReleaseTime = -1;

};

