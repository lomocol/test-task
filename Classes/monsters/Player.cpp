#include "Player.h"

using namespace cocos2d;
using namespace std;

const std::string shieldImageFileName = "skills/circle.png";
const std::string fireBallImageFileName = "skills/fireball.png";
static float shieldTime = 10.0f;
static cocos2d::Size fireBallSize = { 70,70 };
static cocos2d::Vec2 fireBallImpulse = { 0, 550 };

Player::Player(const std::string& filename, cocos2d::Node* _parent, Header* _header, cocos2d::Vec2 position, const BodyInfo& bodyInfo) :
	iMonster(filename, _parent, position, bodyInfo), shotSpawner(nullptr), header(_header)
{
	health = 100;
	protection = 100;
	underSheild = false;

	synchronizeHealth();
	synchronizeProtection();

	sprite->setAnchorPoint(Point(0.5, 0.5));
	sprite->setPosition(position);
	sprite->getPhysicsBody()->setDynamic(true);
	sprite->getPhysicsBody()->setMass(PLAYER_MASS);
	addListeners();

	ImageManager::instance().addTexture(shieldImageFileName, sprite->getContentSize() * 6);
	ImageManager::instance().addTexture(fireBallImageFileName, fireBallSize);
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
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_A:
		sprite->getPhysicsBody()->applyImpulse(Vec2(-13000, 0));
		break;
	case EventKeyboard::KeyCode::KEY_D:
		sprite->getPhysicsBody()->applyImpulse(Vec2(13000, 0));
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		shot();
		break;
	case EventKeyboard::KeyCode::KEY_1:
		createShield();
		break;
	case EventKeyboard::KeyCode::KEY_2:
		createFireball();
		break;
	case EventKeyboard::KeyCode::KEY_3:
		createBlock();
		break;
	default:
		break;
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
	header->changeSkillButton(type, skillCount[type]);
}

void Player::createFireball()
{
	if (skillCount[BonusType::FireBall] == 0)
		return;

	header->changeSkillButton(BonusType::FireBall, --skillCount[BonusType::FireBall]);

	auto fireSprite = Sprite::createWithTexture(ImageManager::instance().getTexture(fireBallImageFileName));
	float fireBallRadius = fireSprite->getContentSize().width / 2;
	auto spriteBody = PhysicsBody::createCircle(fireBallRadius, PhysicsMaterial(0,1,0));
	setBodyInfo(spriteBody,FIREBALL_BODY_INFO);
	fireSprite->setPhysicsBody(spriteBody);

	auto firePosition = sprite->getPosition();
	firePosition.y += sprite->getContentSize().height / 2 + fireBallRadius;
	fireSprite->setPosition(firePosition.x, firePosition.y);

	spriteBody->applyImpulse(fireBallImpulse);
	parent->addChild(fireSprite);
	
}

void Player::createBlock()
{
}

void Player::createShield()
{
	if (skillCount[BonusType::Shield] == 0)
		return;

	header->changeSkillButton(BonusType::Shield, --skillCount[BonusType::Shield]);

	if (!underSheild)
	{
		// create a four-point shield 
		shield = Sprite::createWithTexture(ImageManager::instance().getTexture(shieldImageFileName));
		auto playerSize = sprite->getContentSize();
		const Vec2 vecs[] = {
			{-playerSize.width * 2,-playerSize.height},
			{-playerSize.width,playerSize.height * 2},
			{playerSize.width,playerSize.height * 2},
			{playerSize.width * 2,-playerSize.height}
		};
		auto shieldBody = PhysicsBody::createEdgePolygon(vecs, 4);
		setBodyInfo(shieldBody, SHIELD_BODY_INFO);
		shieldBody->setDynamic(false);
		shield->setPhysicsBody(shieldBody);
		shield->setPosition(playerSize.width / 2, playerSize.height / 2);

		sprite->addChild(shield);
		// remove shield after shieldTime
		auto removeShield = CallFunc::create([&]() {shield->removeFromParent(); underSheild = false;});
		auto delay = DelayTime::create(shieldTime);
		shield->runAction(Sequence::create(delay, removeShield, nullptr));

		underSheild = true;
	}
	else
	{
		// restart shield timer 
		shield->stopAllActions();
		auto removeShield = CallFunc::create([&]() {shield->removeFromParent(); underSheild = false;});
		auto delay = DelayTime::create(shieldTime);
		shield->runAction(Sequence::create(delay, removeShield, nullptr));
	}
}
