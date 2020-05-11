#include "Spider.h"

using namespace std;
using namespace cocos2d;
using namespace ui;

Spider::Spider(const std::string& filename, cocos2d::Node* _parent, cocos2d::Vec2 position,
	const BodyInfo& bodyInfo, int columnNum, const cocos2d::Sprite* player) :
	iMonster(filename, _parent, position, bodyInfo), columnNum(columnNum), player(player)
{
	health = SPIDER_HEALTH;
	dead = false;
}

void Spider::die()
{

	if (sprite == nullptr)
		return;

	auto texture = ImageManager::instance().getTexture("spider_dead.png");
	if (texture != nullptr)
		sprite->setTexture(texture);

	auto pos = sprite->getPosition();
	pos.y = sprite->getContentSize().height;

	auto moveDown = MoveTo::create(SPIDER_FALL_TIME, pos);
	sprite->runAction(moveDown);
	web->removeFromParent();
	dead = true;
}

void Spider::runWeb(float webLenght)
{
	web = LoadingBar::create("bar.png");

	web->setScale(webLenght / web->getContentSize().width, SPIDER_WEB_WIDTH_SCALE);
	web->setDirection(LoadingBar::Direction::LEFT);
	web->setAnchorPoint(Point(0, 0.5));
	web->setRotation(90.0);
	web->setPosition(sprite->getPosition());

	parent->addChild(web);
	web->runAction(ProgressTo::create(SPIDER_APPEARANCE_TIME, 100));
}

void Spider::appearance(float time)
{
	int webLenght = rand() % (SPIDER_WEB_LENGHT_MAX - SPIDER_WEB_LENGHT_MIN) + SPIDER_WEB_LENGHT_MIN;
	runWeb(webLenght);

	auto moveDown = MoveBy::create(SPIDER_APPEARANCE_TIME, Vec2(0, -webLenght));
	sprite->runAction(moveDown);

	auto delay = DelayTime::create(SPIDER_SHOT_INTERVAL);
	auto startShot = CallFunc::create([this]() {shot();});
	auto shotSequence = Sequence::create(delay, startShot, nullptr);
	sprite->runAction(shotSequence);

}

void Spider::causeDamage(int damage)
{
	if (dead)
	{
		sendNotifications();
	}
	else
		iMonster::causeDamage(damage);
}

void Spider::shot()
{
	// create shot sprite
	auto shotSprite = Sprite::create();
	shotSprite->setTextureRect(Rect(Vec2::ZERO, SPIDER_SHOT_SIZE));
	shotSprite->setAnchorPoint(Point(0.5,1));

	auto spriteBody = PhysicsBody::createCircle(SPIDER_SHOT_SIZE.width / 2);
	spriteBody->setDynamic(true);
	setBodyInfo(spriteBody, SPIDER_SHOT_BODY_INFO);
	shotSprite->setPhysicsBody(spriteBody);

	// calculation of the direction and the power of a shot
	Vec2 shotPosition{ sprite->getPosition().x ,sprite->getPosition().y - sprite->getContentSize().height - 5 };
	auto playerPosition = player->getPosition();
	Vec2 impulseVector{ (playerPosition.x - shotPosition.x) * SPIDER_SHOT_POWER, (playerPosition.y - shotPosition.y) * SPIDER_SHOT_POWER };

	// add sprite to arena in the next frame
	DynamicCreator::instance().addCreationOrder({ shotSprite ,shotPosition, parent });

	// emit added shot in the next frame
	parent->scheduleOnce([impulseVector, spriteBody](float delta) {
		spriteBody->applyImpulse(impulseVector);
		}, 0.0, "spiderShot");

	// run shot again after SPIDER_SHOT_INTERVAL time
	auto nextShot = CallFunc::create([this]() {shot();});
	auto delay = DelayTime::create(SPIDER_SHOT_INTERVAL);
	auto shotSequence = Sequence::create(delay, nextShot, nullptr);
	sprite->runAction(shotSequence);
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
		EventCustom event("spider_drop_bonus_event");
		auto topPosition = sprite->getPosition();	// sprite position with anchorPoint(0.5,1)
		Vec2* position = new Vec2(topPosition.x, topPosition.y - sprite->getContentSize().height); // sprite position with anchorPoint(0.5,0)
		event.setUserData(position);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}
	{
		EventCustom event("spider_die_event");
		int* num = new int(tag - SPIDER_TAG);
		event.setUserData(num);
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}
}
