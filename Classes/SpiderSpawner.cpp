#include "spiderSpawner.h"

using namespace std;
using namespace cocos2d;


SpiderSpawner::SpiderSpawner(cocos2d::Node* _parent, ColumnManager* columnManager, int maxMonsterCount) :
	iSpawner(_parent, columnManager, maxMonsterCount)
{
	 spawnInterval = SPIDER_SPAWN_INTERVAL;
	 appearanceTime = SPIDER_APPEARANCE_TIME;
	 columnReleaseTime = SPIDER_COLUMN_RELEASE_TIME;
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
			columnManager->releaseColumnAfter(freeColumn.number, appearanceTime + columnReleaseTime);
		}
	}

	auto delay = DelayTime::create(spawnInterval);
	auto spawnCallFunc = CallFunc::create([this]() {this->spawn();});

	auto sequense = Sequence::create(delay, spawnCallFunc, nullptr);
	spawner->runAction(sequense);
}

