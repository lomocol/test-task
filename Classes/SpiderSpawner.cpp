#include "spiderSpawner.h"

using namespace std;
using namespace cocos2d;


SpiderSpawner::SpiderSpawner(cocos2d::Node* _parent, ColumnManager* columnManager, int maxMonsterCount) :
	iSpawner(_parent, columnManager, maxMonsterCount)
{
	float spawnInterval = SPIDER_SPAWN_INTERVAL;
	float appearanceTime = SPIDER_APPEARANCE_TIME;
	float columnReleaseTime = SPIDER_COLUMN_RELEASE_TIME;
}

void SpiderSpawner::startSpawn()
{
	auto spawnCallFunc = CallFunc::create([this]() {this->spawn();});
	spawner->runAction(spawnCallFunc);
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
			Icicle* ice = new Icicle(ICICLE_IMAGE, parent, position, ICICLE_MASK + spriteNumber);

			ice->appearance(appearanceTime);

			monsters[spriteNumber] = ice;
			columnManager->releaseColumnAfter(freeColumn.number, appearanceTime + columnReleaseTime);
		}
	}

	auto delay = DelayTime::create(spawnInterval);
	auto spawnCallFunc = CallFunc::create([this]() {this->spawn();});

	auto sequense = Sequence::create(delay, spawnCallFunc, nullptr);
	spawner->runAction(sequense);
}

