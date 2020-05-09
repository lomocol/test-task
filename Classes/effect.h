#pragma once

#include "definitions.h"
#include "cocos2d.h"

enum EffectType
{
	Fragment,
	Fire,
	Space
};

class EffectMaker
{
public:
	static EffectMaker& instance()
	{
		static EffectMaker effectMaker;
		return effectMaker;
	}
	void dropDefaultEfffect(cocos2d::Node* parent, cocos2d::Vec2 position, EffectType type, float duration = 0);
	void dropFragments(cocos2d::Node* parent, cocos2d::Vec2 position);
private:
	EffectMaker() {};
	EffectMaker(const EffectMaker&) = delete;
	EffectMaker& operator = (const EffectMaker&) = delete;
private:
	cocos2d::Sprite* createFragment(cocos2d::Node* parent, cocos2d::Vec2 position);
};

