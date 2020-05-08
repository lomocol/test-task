#pragma once
#include "iSpawner.h"
#include "../monsters/bonus.h"

#include <array>

class BonusSpawner : public iSpawner
{

public:
	BonusSpawner(cocos2d::Node* _parent, int maxMonsterCount);
	
private:
	virtual void addListeners();
	BonusType randomBonusType(const std::vector<BonusType> & types);
	void dropSpiderBonus(cocos2d::Vec2 position);
	void dropIcicleBonus(cocos2d::Vec2 position);
	void startSpawn() {};
	void spawn() {};
private:

	const std::vector<BonusType> spiderBonus = { BonusType::Health,BonusType::Protection};
	const std::vector<BonusType>  icicleBonus = { BonusType::Block,BonusType::FireBall,BonusType::Shield };
};

