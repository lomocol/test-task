#include "spiderSpawner.h"

using namespace std;
using namespace cocos2d;


SpiderSpawner::SpiderSpawner(cocos2d::Node* _parent, ColumnManager* columnManager, int maxMonsterCount) :
	iSpawner(_parent, maxMonsterCount, columnManager)
{
	 spawnInterval = SPIDER_SPAWN_INTERVAL;
	 appearanceTime = SPIDER_APPEARANCE_TIME;
	 columnReleaseTime = SPIDER_COLUMN_RELEASE_TIME;
}



void SpiderSpawner::addListeners()
{
	auto dieListener = EventListenerCustom::create("spider_die_event", [=](EventCustom* event) {
		CCLOG("SPIDER EVENT CAUGHT in SPAWNER!!!");
		});
	parent->getEventDispatcher()->addEventListenerWithSceneGraphPriority(dieListener, parent);
}

void SpiderSpawner::spawn()
{

	int spriteNumber = getFreeMonsterNumber();

	if (spriteNumber != -1)
	{
		Column freeColumn = columnManager->getFreeColumn();
		if (freeColumn.number != -1)
		{
			Vec2 position(freeColumn.centerPosition, spawnYPosition);
			BodyInfo bodyInfo = SPIDER_BODY_INFO;
			bodyInfo.tag += spriteNumber;
			Spider* spider = new Spider(SPIDER_IMAGE, parent, position, bodyInfo);

			spider->appearance(appearanceTime);

			monsters[spriteNumber] = spider;
		}
	}

	auto delay = DelayTime::create(spawnInterval);
	auto spawnCallFunc = CallFunc::create([this]() {this->spawn();});

	auto sequense = Sequence::create(delay, spawnCallFunc, nullptr);
	spawner->runAction(sequense);
}

