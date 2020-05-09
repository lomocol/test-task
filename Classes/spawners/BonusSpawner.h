#pragma once
#include "iSpawner.h"
#include "../monsters/bonus.h"

#include <vector>
#include <map>

class BonusSpawner : public iSpawner
{

public:
	BonusSpawner(cocos2d::Node* _parent, int maxMonsterCount);
	void removeBonus(int bonusTag);
private:
	virtual void addListeners();
	BonusType randomBonusType(const std::vector<BonusType> & types);
	void dropSpiderBonus(const cocos2d::Vec2 & position);
	void dropIcicleBonus(const cocos2d::Vec2 & position);
	void startSpawn() {};
	void spawn(BonusType type,const cocos2d::Vec2  position);
	void spawn() {};
private:
	std::map<BonusType, const std::string> typeFileNames;
	const std::vector<BonusType> spiderBonus = { BonusType::Health,BonusType::Protection};
	const std::vector<BonusType>  icicleBonus = { BonusType::Block,BonusType::FireBall,BonusType::Shield };
};

