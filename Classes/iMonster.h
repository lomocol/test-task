#pragma once

#include "cocos2d.h"
#include "definitions.h"
#include "settings.h"



class iMonster
{
public:
	iMonster(const std::string& filename, cocos2d::Node* _parent, cocos2d::Vec2 position,const BodyInfo bodyInfo);
	iMonster(cocos2d::Size size, cocos2d::Node* _parent, cocos2d::Vec2 position, const BodyInfo bodyInfo);
	virtual void die() = 0;
	virtual void changeHealth(float value);
	virtual void appearance(float time) = 0;
protected:
	cocos2d::Node* parent;
	cocos2d::Sprite* sprite;
	float health;
	int tag;
};

