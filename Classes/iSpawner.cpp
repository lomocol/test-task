#include "iSpawner.h"

using namespace cocos2d;

iSpawner::iSpawner(cocos2d::Node* _parent, int _maxMonsterCount, ColumnManager* _columnManager) :parent(_parent) ,
columnManager(_columnManager) , maxMonsterCount(_maxMonsterCount)
{
	monsters.assign(maxMonsterCount,nullptr);
	spawner = Sprite::create();
	parent->addChild(spawner);
	spawnYPosition = parent->getContentSize().height;
}

void iSpawner::startSpawn()
{
	auto spawnCallFunc = CallFunc::create([this]() {this->spawn();});
	spawner->runAction(spawnCallFunc);
}

int iSpawner::getFreeMonsterNumber() const
{
	int number = -1;
	int size = monsters.size();
	for (int i = 0; i < size; i++)
		if (monsters[i] == nullptr)
			return i;
	return number;
}
