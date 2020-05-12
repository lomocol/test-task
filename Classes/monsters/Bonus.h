#pragma once
#include "cocos2d.h"
#include "definitions.h"
#include "iMonster.h"

enum class BonusType {
	Health,
	Protection,
	FireBall,
	Block,
	Shield,
	Empty
};

class Bonus : public iMonster
{

public:
	Bonus(const std::string & filename, cocos2d::Node* _parent, cocos2d::Vec2 position, const BodyInfo bodyInfo, BonusType _type);
private:
	 void appearance(float time) override {};
	 void die() override {} ;
private:
	BonusType type;
};

