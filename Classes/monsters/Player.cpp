#include "Player.h"

using namespace cocos2d;
using namespace std;

Player::Player(const std::string& filename, cocos2d::Node* _parent, Header* _header, cocos2d::Vec2 position, const BodyInfo& bodyInfo) :
	iMonster(filename, _parent, position, bodyInfo), shotSpawner(nullptr), header(_header)
{
	health = 100;
	protection = 100;

	synchronizeHealth();
	synchronizeProtection();

	sprite->setAnchorPoint(Point(0.5, 0));
	sprite->setPosition(position);
	sprite->getPhysicsBody()->setDynamic(true);
	sprite->getPhysicsBody()->setMass(PLAYER_MASS);
	addListeners();
}

void Player::die()
{
	auto texture = ImageManager::instance().getTexture(PLAYER_DEAD_IMAGE);
	sprite->setTexture(texture);
}

void Player::appearance(float time)
{
}

void Player::causeDamage(float domage)
{
	if (protection < domage)
	{
		domage -= protection;
		protection = 0;
		health -= domage;
		synchronizeHealth();
		if (health <= 0)
			die();
	}
	else
		protection -= domage;

	synchronizeProtection();
}

void Player::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
		if (keyCode == EventKeyboard::KeyCode::KEY_A)
		{
			sprite->getPhysicsBody()->applyImpulse(Vec2(-13000, 0));
		}
		else
			if (keyCode == EventKeyboard::KeyCode::KEY_D)
			{
				sprite->getPhysicsBody()->applyImpulse(Vec2(13000, 0));
			}
				else
					if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
					{
						shot();
					}
}

void Player::activateBonus(BonusType type)
{
	switch (type)
	{
	case BonusType::Health:
		health = 100;
		synchronizeHealth();
		break;
	case BonusType::Protection:
		protection = 100;
		synchronizeProtection();
		break;
	case BonusType::Empty:
		break;
	default:
		skillCount[type] += 1;
		header->changeSkillButton(type, skillCount[type]);
		break;
	}
	
}

void Player::shot()
{
	shotSpawner->spawn();
}

void Player::addListeners()
{
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Player::keyPressed, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, sprite);
}

void Player::synchronizeHealth()
{
	header->changeHealth(health);
}

void Player::synchronizeProtection()
{
	header->changeProtection(protection);
}

void Player::synchronizeSkill(BonusType type)
{
	header->changeSkillButton(type,skillCount[type]);
}

void Player::createFireball()
{
}

void Player::createBlock()
{
}

void Player::createShield()
{
}
