#pragma once
#include "iMonster.h"
class Block :
	public iMonster
{
public:
	Block(cocos2d::Texture2D * texture, cocos2d::Node* _parent, cocos2d::Vec2 position, const BodyInfo& bodyInfo);
	void die() override;
	
private:
	void appearance(float time) override {};
	void sendNotifications();
};

