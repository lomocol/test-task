#include "Spider.h"

using namespace std;
using namespace cocos2d;
using namespace ui;

Spider::Spider(const std::string& filename, cocos2d::Node* _parent, cocos2d::Vec2 position, const BodyInfo & bodyInfo, int columnNum) :
	iMonster(filename,_parent, position, bodyInfo),columnNum(columnNum)
{
	health = SPIDER_HEALTH;
	dead = false;
}

void Spider::die()
{

	if (sprite == nullptr)
		return;

	auto texture = ImageManager::instance().getTexture("spider_dead.png");
	if(texture != nullptr)
		sprite->setTexture(texture);

	auto pos = sprite->getPosition();
	pos.y = sprite->getContentSize().height;

	auto moveDown = MoveTo::create(SPIDER_FALL_TIME, pos);
	sprite->runAction(moveDown);
	web->removeFromParent();
	dead = true;
}

void Spider::appearance(float time)
{
	int webLenght = rand() % (SPIDER_WEB_LENGHT_MAX - SPIDER_WEB_LENGHT_MIN) + SPIDER_WEB_LENGHT_MIN;

	web = LoadingBar::create("bar.png");

	web->setScale(webLenght / web->getContentSize().width, SPIDER_WEB_WIDTH_SCALE);
	web->setDirection(LoadingBar::Direction::LEFT);
	web->setAnchorPoint(Point(0,0.5));
	web->setRotation(90.0);
	web->setPosition(sprite->getPosition());

	parent->addChild(web);
	web->runAction(ProgressTo::create(SPIDER_APPEARANCE_TIME, 100));

	auto spiderMoveDown = MoveBy::create(SPIDER_APPEARANCE_TIME,Vec2(0,-webLenght));
	sprite->runAction(spiderMoveDown);

}

void Spider::causeDamage(int damage)
{
	if (dead)
	{
		sendNotifications();
		//sprite->removeFromParent();
	}
	else
		iMonster::causeDamage(damage);
}



void Spider::sendNotifications()
{
	{
		EventCustom event("release_column_event");
		int* column = new int(columnNum);
		event.setUserData(column);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}
	{
		EventCustom event("spider_die_event");
		int* num = new int(tag - SPIDER_TAG);
		event.setUserData(num);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}
	
}
