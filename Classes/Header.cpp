#include "Header.h"

using namespace cocos2d;
using namespace ui;
using namespace std;

Header::Header(cocos2d::Node* _parent)
{
	parent = _parent;
	headerSize = parent->getContentSize();
	setBackground();
	createBars();
}

void Header::changeHealth(float newHealth)
{
	healthBar->runAction(ProgressTo::create(0.5f, newHealth));
}

void Header::changeProtection(float newProtection)
{
	protectionBar->runAction(ProgressTo::create(0.5f, newProtection));
}



void Header::createBars()
{

	Vec2 healthPos();
	Vec2 protectionPos();

	healthBar = LoadingBar::create("bar.png");
	healthBar->setColor(Color3B::RED);
	healthBar->setDirection(LoadingBar::Direction::LEFT);
	healthBar->setAnchorPoint({ 0,0 });
	healthBar->setPosition({ 20,20 });
	//healthBar->runAction(ProgressTo::create(3.0f, 100.0f));
	parent->addChild(healthBar);

	protectionBar = LoadingBar::create("bar.png");
	protectionBar->setColor(Color3B::GREEN);
	protectionBar->setDirection(LoadingBar::Direction::LEFT);
	protectionBar->setAnchorPoint({ 0,0 });
	protectionBar->setPosition({ 20,100 });
	//protectionBar->runAction(ProgressTo::create(3.0f, 100.0f));
	parent->addChild(protectionBar);
}

void Header::setBackground()
{
	auto sprite = Sprite::create();
	sprite->setTextureRect(Rect(0, 0, headerSize.width, headerSize.height));
	sprite->setColor(Color3B::YELLOW);
	sprite->setAnchorPoint(Point(0, 0));
	sprite->setPosition(0, 0);
	parent->addChild(sprite);
}
