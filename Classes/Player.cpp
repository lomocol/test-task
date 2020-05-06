#include "Player.h"

using namespace cocos2d;
using namespace std;

Player::Player(const std::string & filename, cocos2d::Node* _parent, Header* _header, cocos2d::Vec2 position, const BodyInfo & bodyInfo) :
	iMonster(filename,_parent, position, bodyInfo)
{
	header = _header;

	health = 100;
	protection = 100;

	synchronizeHealth();
	synchronizeProtection();

	sprite->setAnchorPoint(Point(0.5, 0));
	sprite->setPosition(position);
	sprite->getPhysicsBody()->setDynamic(true);

	addListeners();
}

void Player::die()
{
}

void Player::appearance(float time)
{
}

void Player::causeDomage(float domage)
{
	if (protection < domage)
	{
		domage -= protection;
		protection = 0;
		synchronizeHealth();
		changeHealth(-domage);
	}
	else
		protection -= domage;

	synchronizeProtection();
}

void Player::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		sprite->getPhysicsBody()->applyImpulse(Vec2(0, 100));
	}
	else
		if (keyCode == EventKeyboard::KeyCode::KEY_A)
		{
			sprite->getPhysicsBody()->applyImpulse(Vec2(-100, 0));
		}
		else
			if (keyCode == EventKeyboard::KeyCode::KEY_D)
			{
				sprite->getPhysicsBody()->applyImpulse(Vec2(100, 0));
			}
			else
				if (keyCode == EventKeyboard::KeyCode::KEY_S)
				{
					sprite->getPhysicsBody()->applyImpulse(Vec2(0, -100));
				}

}
bool Player::onContactBegin(cocos2d::PhysicsContact& contact)
{
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	auto one = a->getCollisionBitmask();
	auto two = b->getCollisionBitmask();

	return false;
}
void Player::addListeners()
{
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Player::keyPressed, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, sprite);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Player::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, sprite);

}

void Player::synchronizeHealth()
{
	header->changeHealth(health);
}

void Player::synchronizeProtection()
{
	header->changeProtection(protection);
}
