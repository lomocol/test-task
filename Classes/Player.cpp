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
	sprite->setPosition(arenaSize.width / 2, 0);
	auto spriteBody = PhysicsBody::createCircle(sprite->getContentSize().width / 2);
	spriteBody->setCollisionBitmask(PLAYER_MASK);
	spriteBody->setContactTestBitmask(true);
	sprite->setPhysicsBody(spriteBody);

	parent->addChild(sprite);
}

void Player::synchronizeHealth()
{
	header->changeHealth(health);
}

void Player::synchronizeProtection()
{
	header->changeProtection(protection);
}
