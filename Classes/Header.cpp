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
	ImageManager::instance().addTexture(HEADER_IMAGE, headerSize);
	auto texture = ImageManager::instance().getTexture(HEADER_IMAGE);
	background = Sprite::createWithTexture(texture);
	background->setAnchorPoint(Point(0, 0));
	background->setPosition(0, 0);
	parent->addChild(background);
}
