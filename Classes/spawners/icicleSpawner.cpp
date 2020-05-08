#include "icicleSpawner.h"

using namespace std;
using namespace cocos2d;


IcicleSpawner::IcicleSpawner(cocos2d::Node* _parent, ColumnManager* columnManager , int maxMonsterCount) :
	iSpawner(_parent, maxMonsterCount,columnManager)
{
	 spawnInterval = ICICLE_SPAWN_INTERVAL;
	 appearanceTime = ICICLE_APPEARANCE_TIME;
	 columnReleaseTime = ICICLE_COLUMN_RELEASE_TIME;
	 addListeners();
}

void IcicleSpawner::addListeners()
{
	auto dieListener = EventListenerCustom::create("icicle_die_event", [=](EventCustom* event) {
		int* num = static_cast<int*>(event->getUserData());
		releaseMonster(*num);
		delete num;
		});
	parent->getEventDispatcher()->addEventListenerWithSceneGraphPriority(dieListener, parent);
}

void IcicleSpawner::spawn()
{

	int spriteNumber = getFreeMonsterNumber();

	if (spriteNumber != -1)
	{
		Column freeColumn = columnManager->getFreeColumn();
		if (freeColumn.number != -1)
		{
			Vec2 position(freeColumn.centerPosition, spawnYPosition);

			BodyInfo bodyInfo = ICICLE_BODY_INFO;
			bodyInfo.tag += spriteNumber;
			Icicle* icicle = new Icicle(ICICLE_IMAGE, parent, position, bodyInfo);

			icicle->appearance(appearanceTime);

			monsters[spriteNumber] = icicle;
			columnManager->releaseColumnAfter(freeColumn.number, appearanceTime + columnReleaseTime);
		}
	}

	auto delay = DelayTime::create(spawnInterval);
	auto spawnCallFunc = CallFunc::create([this]() {this->spawn();});
	auto sequense = Sequence::create(delay, spawnCallFunc, nullptr);
	spawner->runAction(sequense);
}

