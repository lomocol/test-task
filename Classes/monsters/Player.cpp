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
		synchronizeHealth();
		health -= domage;
		if (health <= 0)
			die();
	}
	else
		protection -= domage;

	synchronizeProtection();
}

void Player::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		sprite->getPhysicsBody()->applyImpulse(Vec2(0, 50000));
	}
	else
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
				if (keyCode == EventKeyboard::KeyCode::KEY_S)
				{
					sprite->getPhysicsBody()->applyImpulse(Vec2(0, -2000));
				}
				else
					if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
					{
						shot();
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
