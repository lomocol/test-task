#include "iSpawner.h"

using namespace cocos2d;

iSpawner::iSpawner(cocos2d::Node* _parent, ColumnManager* _columnManager, int _maxMonsterCount) :parent(_parent) ,
columnManager(_columnManager) , maxMonsterCount(_maxMonsterCount)
{
	monsters.assign(maxMonsterCount,nullptr);
	spawner = Sprite::create();
	parent->addChild(spawner);
	spawnYPosition = parent->getContentSize().height;
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