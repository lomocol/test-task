#pragma once

#include "cocos2d.h"
#include "definitions.h"
#include "Header.h"
#include "iMonster.h"
#include "../spawners/ShotSpawner.h"

class Player : public iMonster
{
public:
	Player(const std::string& filename, cocos2d::Node* _parent, Header* _header, cocos2d::Vec2 position, const BodyInfo& bodyInfo);
	void causeDamage(float domage);
	void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void die() override;
	void appearance(float time) override;
	void setShotSpiwner(ShotSpawner* _shotSpawner) { shotSpawner = _shotSpawner; };
	const cocos2d::Sprite* getSprite() { return sprite; };
private:
	void shot();
	void addListeners();
	void synchronizeHealth();
	void synchronizeProtection();
private:
	Header* header;
	float protection;
	ShotSpawner* shotSpawner;
};
