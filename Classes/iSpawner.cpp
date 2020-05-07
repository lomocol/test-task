#include "iSpawner.h"

using namespace cocos2d;

iSpawner::iSpawner(cocos2d::Node* _parent, int _maxMonsterCount, ColumnManager* _columnManager) :parent(_parent) ,
columnManager(_columnManager) , maxMonsterCount(_maxMonsterCount)
{
	monsters.assign(maxMonsterCount,nullptr);
	spawner = Sprite::create();
	parent->addChild(spawner);
	spawnYPosition = parent->getContentSize().height;

	addListeners();
}

void iSpawner::startSpawn()
{
	auto spawnCallFunc = CallFunc::create([this]() {this->spawn();});
	spawner->runAction(spawnCallFunc);
}

void iSpawner::causeDamage(int monsterNumber,int damage)
{
	auto monster = monsters[monsterNumber];
	if (monster != nullptr)
	{
		if (monster->causeDamage(damage))
		{
 			delete monster;
			monsters[monsterNumber] = nullptr;
		}
	}
}

void iSpawner::addListeners()
{
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
