#pragma once

#include "cocos2d.h"
#include "definitions.h"
#include "Header.h"

class Player
{
public:
	Player(cocos2d::Node * _parent, Header * _header = nullptr);
private:
	void synchronizeHealth();
	void synchronizeProtection();
	cocos2d::Sprite * sprite;
	Header * header;
	cocos2d::Node* parent;
	float health;
	float protection;
};
