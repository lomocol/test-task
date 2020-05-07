#include "Shot.h"

Shot::Shot(cocos2d::Size size, cocos2d::Vec2 shotDirection, cocos2d::Node* _parent, cocos2d::Vec2 position, const BodyInfo bodyInfo) :
	iMonster(size,_parent,position,bodyInfo)
{
	appearance(SHOT_APPEARANCE_TIME);
	sprite->getPhysicsBody()->applyImpulse(shotDirection);
}

void Shot::die()
{
}

void Shot::appearance(float time)
{

}
