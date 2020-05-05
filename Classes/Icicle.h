#pragma once
#include "cocos2d.h"
#include "definitions.h"

class Icicle
{
public:
	Icicle(cocos2d::Node* _parent, cocos2d::Vec2 position, int mask);

	cocos2d::Sprite* getSprite() noexcept { return sprite; };
	void growingUp(float time);
	void destroy();

private:
	void firstStage();
	void secondStage();
	void thirdStage();

private:
	cocos2d::Node* parent;
	cocos2d::Sprite* sprite;
	//cocos2d::CallFunc * firstStage;
	//cocos2d::CallFunc * secondStage;
	//cocos2d::CallFunc * thirdStage;
};

