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
				else
					if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
					{
						shot();
						return;
						auto sprite2 = Sprite::create();

						sprite2->setTextureRect(Rect(Vec2(0, 0), { 20,20 }));
						sprite2->setAnchorPoint(Point(0.5f, 0.0f));
						auto pos = sprite->getPosition();
						pos.y += 33;
						sprite2->setPosition({100,100});

						auto spriteBody = PhysicsBody::createBox({ 20,20 }, PhysicsMaterial(0, 1, 0));
						spriteBody->setDynamic(true);
						setBodyInfo(spriteBody, FRAGMENT_BODY_INFO);

						sprite2->setPhysicsBody(spriteBody);
						parent->addChild(sprite2);
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
