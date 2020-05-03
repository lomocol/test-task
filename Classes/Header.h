#pragma once
#include "cocos2d.h"
#include "definitions.h"
#include "ui/CocosGUI.h"

class Header
{
public:
	Header(cocos2d::Node* _parent);
	void changeHealth(float newHealth);
	void changeProtection(float newProtection);

private:
	cocos2d::Size headerSize;
	void createBars();
	void setBackground();
	cocos2d::Node* parent;
	cocos2d::ui::LoadingBar* healthBar;
	cocos2d::ui::LoadingBar* protectionBar;
};

