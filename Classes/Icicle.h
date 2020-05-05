#pragma once
#include "cocos2d.h"
#include "definitions.h"
#include "iMonster.h"

class Icicle : public iMonster
{
public:
	Icicle(const std::string& filename, cocos2d::Node* _parent, cocos2d::Vec2 position, int mask);
	void die() override;
	void appearance(float time) override;
private:
	void firstStage();
	void secondStage();
	void thirdStage();

};

