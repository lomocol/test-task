#include "spawnManager.h"

using namespace std;
using namespace cocos2d;

SpawnManager::SpawnManager(cocos2d::Node* _parent):parent(_parent)
{
	columnCount = 10;
	growingUpTime = 3;
	arenaSize = parent->getContentSize();
	columnManager = new ColumnManager(parent,parent->getContentSize().width, columnCount);
	icicleWidth = arenaSize.width / columnCount;
	renderTextures();
	
	int max_icicle_count = 10;
	icicles.assign(max_icicle_count, nullptr);
}

void SpawnManager::startIcicleSpawn()
{
	isicleSpawner = Sprite::create();
	auto callback = CallFunc::create([this]() {this->spawnIcicle();});
	auto sequense = Sequence::create(callback, nullptr);

	parent->addChild(isicleSpawner);
	isicleSpawner->runAction(sequense);
}

int randomFromVector(const vector<int>& numbers)
{
	return numbers[rand() % numbers.size()];
}

void SpawnManager::renderTextures()
{
	ImageManager::instance().addTexture("icicle1.png", Size(icicleWidth, 30));
	ImageManager::instance().addTexture("icicle2.png", Size(icicleWidth, 45));
	ImageManager::instance().addTexture("icicle3.png", Size(icicleWidth, 55));
}

void SpawnManager::spawnIcicle()
{

	int spriteNumber = getFreeSpriteNumber();
	
	if (spriteNumber != -1)
	{
		Column freeColumn = columnManager->getFreeColumn();
		if (freeColumn.number != -1)
		{
			Vec2 position(freeColumn.centerPosition, arenaSize.height);
			Icicle* ice = new Icicle(parent, position, ICICLE_MASK + spriteNumber);

			ice->growingUp(growingUpTime);

			icicles[spriteNumber] = ice;
			columnManager->releaseColumnAfter(freeColumn.number, growingUpTime + 0.5);
		}
	}

	auto delay = DelayTime::create(1);
	auto callback = CallFunc::create([this]() {this->spawnIcicle();});

	auto sequense = Sequence::create(delay, callback, nullptr);
	isicleSpawner->runAction(sequense);
}

int SpawnManager::getFreeSpriteNumber()
{
	int num = -1;
	for (int i = 0; i < icicles.size(); i++)
		if (icicles[i] == nullptr) 
			return i;
	return num;
}
