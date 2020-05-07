#pragma once
#include "cocos2d.h"
#include "definitions.h"
#include "settings.h"
#include "ColumnManager.h"
#include "iSpawner.h"
#include "spider.h"

class SpiderSpawner : public iSpawner
{
public:
	SpiderSpawner(cocos2d::Node* _parent, ColumnManager* columnManager, int maxMonsterCount);
	void causeDamage(int monsterNumber, int damage) override;
private:
	void addListeners() override;
	void spawn() override;
private:
	std::vector<int> busyColumns;
};