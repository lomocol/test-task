#pragma once
#include "cocos2d.h"
#include "definitions.h"
#include "iMonster.h"
#include "ui/CocosGUI.h"

class Spider : public iMonster
{
public:
	Spider(const std::string& filename, cocos2d::Node* _parent, cocos2d::Vec2 position, const BodyInfo & bodyInfo);
	void die() override;
	void appearance(float time) override;
private:

};

