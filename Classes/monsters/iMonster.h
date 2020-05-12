#pragma once

#include "cocos2d.h"
#include "definitions.h"
#include "settings.h"
#include "effect.h"


class iMonster
{
public:
	iMonster(const std::string& filename, cocos2d::Node* _parent, cocos2d::Vec2 position,const BodyInfo bodyInfo,bool dynamic = false);
	iMonster(cocos2d::Size size, cocos2d::Node* _parent, cocos2d::Vec2 position, const BodyInfo bodyInfo);
	virtual void die() = 0;
	virtual void causeDamage(int damage);
	virtual void appearance(float time) = 0;
	~iMonster();
protected:
	cocos2d::Node* parent;
	cocos2d::Sprite* sprite;
	int health;
	int tag;
};

