#include "Spider.h"

using namespace std;
using namespace cocos2d;
using namespace ui;

Spider::Spider(const std::string& filename, cocos2d::Node* _parent, cocos2d::Vec2 position, const BodyInfo & bodyInfo) :
	iMonster(filename,_parent, position, bodyInfo)
{

}

void Spider::die()
{
	//EventCustom event("spider_event");
	//Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

void Spider::appearance(float time)
{
	int webLenght = rand() % (SPIDER_WEB_LENGHT_MAX - SPIDER_WEB_LENGHT_MIN) + SPIDER_WEB_LENGHT_MIN;

	LoadingBar * web = LoadingBar::create("bar.png");

	web->setScale(webLenght / web->getContentSize().width, SPIDER_WEB_WIDTH_SCALE);
	web->setDirection(LoadingBar::Direction::LEFT);
	web->setAnchorPoint(Point(0,0.5));
	web->setRotation(90.0);
	web->setPosition(sprite->getPosition());

	parent->addChild(web);
	web->runAction(ProgressTo::create(SPIDER_APPEARANCE_TIME, 100));

	auto spiderMoveDown = MoveBy::create(SPIDER_APPEARANCE_TIME,Vec2(0,-webLenght));
	auto webRemove = CallFunc::create([this, web]() {parent->removeChild(web);});
	auto sequence = Sequence::create(spiderMoveDown, webRemove,nullptr);

	sprite->runAction(sequence);
	
}
