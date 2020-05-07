#pragma once
#include "iMonster.h"
class Shot :
	public iMonster
{
public:
	Shot(cocos2d::Size size, cocos2d::Vec2 shotDirection, cocos2d::Node* _parent, cocos2d::Vec2 position, const BodyInfo bodyInfo);
	void die();
	void appearance(float time);
private:
	void changeHealth() = delete;
};

