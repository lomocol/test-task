#pragma once
#include "cocos2d.h"
#include "definitions.h"
#include "settings.h"
#include "ColumnManager.h"
#include "../monsters/iMonster.h"
#include <vector>
class iSpawner
{
public:
	iSpawner(cocos2d::Node* _parent,  int maxMonsterCount, ColumnManager* columnManager = nullptr);
	void startSpawn();
	void causeDamage(int monsterNumber, int damage);
protected:
	virtual void addListeners();
	virtual void spawn() = 0;
	int getFreeMonsterNumber() const;
protected:
	ColumnManager* columnManager;
	cocos2d::Node* parent;
	std::vector<iMonster*> monsters;
	cocos2d::Sprite* spawner;

	float spawnYPosition;
	int maxMonsterCount;
	float spawnInterval;
	float appearanceTime;
	float columnReleaseTime;

};

