#pragma once
#include "cocos2d.h"
#include "definitions.h"
#include "iMonster.h"
#include "ui/CocosGUI.h"

class Spider : public iMonster
{
public:
	Spider(const std::string& filename, cocos2d::Node* _parent, cocos2d::Vec2 position,
		const BodyInfo & bodyInfo, int columnNum, const cocos2d::Sprite* player);
	void die() override;
	void appearance(float time) override;
	void causeDamage(int damage) override;
private:
	void runWeb(float webLenght);
	void shot();
	void sendNotifications();
private:
	bool dead;
	int columnNum;
	cocos2d::ui::LoadingBar* web;
	const cocos2d::Sprite* player;
};

