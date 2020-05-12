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
	barNode->setAnchorPoint(Point(0, 0));
	barNode->setContentSize(barNodeSize);
	barNode->setPosition(Point(0, 0));
	parent->addChild(barNode, 2);

	// add node for skills buttons
	buttonNode = Node::create();
	buttonNode->setAnchorPoint(Point(0, 0));
	buttonNode->setContentSize(buttonNodeSize);
	buttonNode->setPosition(Point(barNodeSize.width, 0));
	parent->addChild(buttonNode, 2);

	setBackground();
	createBars();
	createButtons();
	createLabels();
}

void Header::changeHealth(float newHealth)
{
	healthBar->runAction(ProgressTo::create(0.5f, newHealth));
}

void Header::changeProtection(float newProtection)
{
	protectionBar->runAction(ProgressTo::create(0.5f, newProtection));
}

void Header::changeSkillButton(BonusType type, int count)
{
	Button* button = buttons[type];
	Label* label = labels[type];

	label->setString(to_string(count));
	if (count > 0)
	{
		if (!button->isEnabled())
			button->setEnabled(true);
	}
	else
		button->setEnabled(false);
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
	const Size barNodeSize = barNode->getContentSize();
	const int barHeight = barNodeSize.height * BAR_HEIGHT_PERCENT;
	const int barWidth = barNodeSize.width * BAR_WIDTH_PERCENT;
	const int verticalPadding = (barNodeSize.height - 2 * barHeight) / 3;
	const int horizontalPadding = (barNodeSize.width - barWidth) / 2;
	const Vec2 healthPosition(horizontalPadding, verticalPadding);
	const Vec2 protectionPosition(horizontalPadding, verticalPadding * 2 + barHeight);



	healthBar = LoadingBar::create("bar.png");
	// calculate scale value to resize bar.png
	const Size rawBarSize = healthBar->getContentSize();
	const Vec2 scaleVal(barWidth / rawBarSize.width, barHeight / rawBarSize.height);

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
	// calculate buttons position
	const Size buttonNodeSize = buttonNode->getContentSize();
	const int buttonWidth = buttonNodeSize.width * buttonWidthPercent;
	const int buttonHeight = buttonNodeSize.height * buttonHeightPercent;
	const int horizontalPadding = (buttonNodeSize.width - 3 * buttonWidth) / 4;
	const int verticalCenter = buttonNodeSize.height / 2;
	const Vec2 firstButtonPosition(horizontalPadding, verticalCenter);
	const Vec2 secondButtonPosition(firstButtonPosition.x + horizontalPadding + buttonWidth, verticalCenter);
	const Vec2 thirdButtonPosition(secondButtonPosition.x + horizontalPadding + buttonWidth, verticalCenter);
	const Size buttonSize(buttonWidth, buttonHeight);


	addButton(BonusType::Shield, shieldButtonFileName, shieldButtonUnavailableFileName, firstButtonPosition, buttonSize);
	addButton(BonusType::FireBall, fireBallButtonFileName, fireBallButtonUnavailableFileName, secondButtonPosition, buttonSize);
	addButton(BonusType::Block, blockButtonFileName, blockButtonUnavailableFileName, thirdButtonPosition, buttonSize);

}

void Header::createLabels()
{
	for (auto& [type, button] : buttons)
	{
		auto& label = labels[type];
		
		label = Label::createWithSystemFont("My Label Text", "Arial", 22);
		auto buttonPosition = button->getPosition();
		auto buttonSize = Size(button->getContentSize().width * button->getScaleX(), button->getContentSize().height* button->getScaleY());
		label->setPosition(buttonPosition.x + buttonSize.width, buttonPosition.y + buttonSize.height / 2);
		label->setString("0");
		buttonNode->addChild(label);
	}
}

void Header::setBackground()
{
	ImageManager::instance().addTexture(HEADER_IMAGE, headerSize);
	auto texture = ImageManager::instance().getTexture(HEADER_IMAGE);
	background = Sprite::createWithTexture(texture);
	background->setAnchorPoint(Point(0, 0));
	background->setPosition(0, 0);
	parent->addChild(background, 1);
}

void Header::addButton(BonusType type, const std::string& normalImageFileName,
	const std::string& unavailableImageFileName, const cocos2d::Vec2 position, const cocos2d::Size buttonSize)
{
	auto& button = buttons[type];
	button = Button::create(normalImageFileName, normalImageFileName, unavailableImageFileName);
	button->setEnabled(false);
	Size rawButtonSize = button->getContentSize();
	Vec2 scaleValue(buttonSize.width / rawButtonSize.width, buttonSize.height / rawButtonSize.height);
	button->setScale(scaleValue.x, scaleValue.y);
	button->setAnchorPoint(Point(0, 0.5));
	button->setPosition(position);
	buttonNode->addChild(button);
}
