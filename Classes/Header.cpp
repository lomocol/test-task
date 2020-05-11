#include "Header.h"

using namespace cocos2d;
using namespace ui;
using namespace std;

Header::Header(cocos2d::Node* _parent)
{
	parent = _parent;
	headerSize = parent->getContentSize();

	Size barNodeSize(headerSize.width * BAR_NODE_SIZE_PERCENT, headerSize.height);
	Size buttonNodeSize(headerSize.width * (1.0f - BAR_NODE_SIZE_PERCENT), headerSize.height);

	// add node for health and protection bars
	barNode = Node::create();
	barNode->setAnchorPoint(Point(0,0));
	barNode->setContentSize(barNodeSize);
	barNode->setPosition(Point(0,0));
	parent->addChild(barNode,2);

	// add node for skills buttons
	//buttonNode = Node::create();
	//buttonNode->setAnchorPoint(Point(0, 0));
	//buttonNode->setContentSize(buttonNodeSize);
	//buttonNode->setPosition(Point(0, 0));
	//parent->addChild(buttonNode);

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

Header::~Header()
{
	background->removeFromParent();
	protectionBar->removeFromParent();
	healthBar->removeFromParent();
}



void Header::createBars()
{
	// calculate bars position
	Size barNodeSize = barNode->getContentSize();
	int barHeight = barNodeSize.height * BAR_HEIGHT_PERCENT;
	int barWidth = barNodeSize.width * BAR_WIDTH_PERCENT;
	int verticalPadding = (barNodeSize.height - 2 * barHeight) / 3;
	int horizontalPadding = (barNodeSize.width - barWidth) / 2;
	Vec2 healthPosition(horizontalPadding, verticalPadding);
	Vec2 protectionPosition(horizontalPadding, verticalPadding * 2 + barHeight);

	

	healthBar = LoadingBar::create("bar.png");
	// calculate scale value to resize bar.png
	Size rawBarSize = healthBar->getContentSize();
	Vec2 scaleVal(barWidth / rawBarSize.width , barHeight / rawBarSize.height);

	healthBar->setColor(Color3B::RED);
	healthBar->setDirection(LoadingBar::Direction::LEFT);
	healthBar->setAnchorPoint({ 0,0 });
	healthBar->setScale(scaleVal.x, scaleVal.y);
	healthBar->setPosition(healthPosition);
	barNode->addChild(healthBar);

	protectionBar = LoadingBar::create("bar.png");
	protectionBar->setColor(Color3B::GREEN);
	protectionBar->setDirection(LoadingBar::Direction::LEFT);
	protectionBar->setAnchorPoint({ 0,0 });
	protectionBar->setScale(scaleVal.x, scaleVal.y);
	protectionBar->setPosition(protectionPosition);
	barNode->addChild(protectionBar);
}

void Header::createButtons()
{
	
}

void Header::setBackground()
{
	ImageManager::instance().addTexture(HEADER_IMAGE, headerSize);
	auto texture = ImageManager::instance().getTexture(HEADER_IMAGE);
	background = Sprite::createWithTexture(texture);
	background->setAnchorPoint(Point(0, 0));
	background->setPosition(0, 0);
	parent->addChild(background,1);
}
