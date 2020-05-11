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
	~Header() ;
private:
	void createBars();
	void setBackground();
private:
	cocos2d::Sprite* background;
	cocos2d::Size headerSize;
	cocos2d::Node* parent;
	cocos2d::Node* buttonNode;
	cocos2d::Node* barNode;
	cocos2d::ui::LoadingBar* healthBar;
	cocos2d::ui::LoadingBar* protectionBar;
};

