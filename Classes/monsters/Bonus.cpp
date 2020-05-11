#include "Bonus.h"

using namespace std;
using namespace cocos2d;

Bonus::Bonus(const std::string& filename, cocos2d::Node* _parent, cocos2d::Vec2 position, const BodyInfo bodyInfo, BonusType _type) :
	iMonster(filename, _parent, position, bodyInfo,true), type(_type)
{
	auto spriteBody = sprite->getPhysicsBody();
	spriteBody->setDynamic(true);
	spriteBody->addMass(BONUS_MASS);
	sprite->setAnchorPoint({ 0.5,0 });

}
