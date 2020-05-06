#pragma once

#include "cocos2d.h"
#include "definitions.h"
#include "Header.h"
#include "iMonster.h"

class Player : public iMonster
{
public:
	Player(const std::string& filename, cocos2d::Node* _parent, Header* _header, cocos2d::Vec2 position, const BodyInfo & bodyInfo);
	bool onContactBegin(cocos2d::PhysicsContact& contact);
	void causeDomage(float domage);
	void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void die() override;
	void appearance(float time) override;
private:
	void addListeners();
	void synchronizeHealth();
	void synchronizeProtection();
	Header* header;
	float protection;
};
