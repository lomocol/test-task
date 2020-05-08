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
	void dropSpiderBonus(const cocos2d::Vec2 & position);
	void dropIcicleBonus(const cocos2d::Vec2 & position);
	void startSpawn() {};
	void spawn(BonusType type,const cocos2d::Vec2  position);
	void spawn() {};
private:

	const std::vector<BonusType> spiderBonus = { BonusType::Health,BonusType::Protection};
	const std::vector<BonusType>  icicleBonus = { BonusType::Block,BonusType::FireBall,BonusType::Shield };
};

