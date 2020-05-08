#pragma once
#include "cocos2d.h"
#include "definitions.h"
#include "iMonster.h"

class Bonus : public iMonster
{
	enum class BonusType {
		Health,
		Protection,
		FireBall,
		Block,
		Sheil,
	};
public:
	Bonus(cocos2d::Size size, cocos2d::Node* _parent, cocos2d::Vec2 position, const BodyInfo bodyInfo, BonusType _type);
	const BonusType type;
private:
	
};

