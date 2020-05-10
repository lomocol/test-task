#pragma once
#include "cocos2d.h"
#include "definitions.h"
#include "settings.h"
#include "ColumnManager.h"
#include "iSpawner.h"
#include "../monsters/spider.h"

class SpiderSpawner : public iSpawner
{
public:
	SpiderSpawner(cocos2d::Node* _parent, ColumnManager* columnManager, int maxMonsterCount,const cocos2d::Sprite * player);
private:
	void addListeners() override;
	void spawn() override;
private:
	const cocos2d::Sprite* player;
};