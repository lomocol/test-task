#include "Player.h"

using namespace cocos2d;
using namespace std;

Player::Player(cocos2d::Node* _parent, Header* _header)
{
	parent = _parent;
	header = _header;

	health = 100;
	protection = 100;
	
	synchronizeHealth();
	synchronizeProtection();
	
	auto arenaSize = parent->getContentSize();
	sprite = Sprite::create("player.png");
	sprite->setAnchorPoint(Point(0.5, 0));
	sprite->setPosition(arenaSize.width / 2, 10);
	auto spriteBody = PhysicsBody::createCircle(sprite->getContentSize().width / 2, PhysicsMaterial(0, 1, 0));
	spriteBody->setCollisionBitmask(PLAYER_MASK);
	spriteBody->setContactTestBitmask(true);
	sprite->setPhysicsBody(spriteBody);
	
	parent->addChild(sprite);

	addListeners();
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
