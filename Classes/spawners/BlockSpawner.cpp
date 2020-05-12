#include "BlockSpawner.h"

using namespace std;
using namespace cocos2d;

static Size blockSize = {100,30};
static const string blockFileName = "skills/block.jpg";

BlockSpawner::BlockSpawner(cocos2d::Node* _parent, int maxMonsterCount):
	iSpawner(_parent, maxMonsterCount)
{
	ImageManager::instance().addTexture(blockFileName,blockSize);
	addListeners();
}

void BlockSpawner::spawn(cocos2d::Vec2 position)
{
	int spriteNumber = getFreeMonsterNumber();

	if (spriteNumber != -1)
	{
		auto texture = ImageManager::instance().getTexture(blockFileName);
		Block* block = new Block(texture,parent,position,BLOCK_BODY_INFO);

		monsters[spriteNumber] = block;
	}

}

void BlockSpawner::addListeners()
{
	auto dieBlockListener = EventListenerCustom::create("block_die_event", [=](EventCustom* event) {
		int* num = static_cast<int*>(event->getUserData());
		releaseMonster(*num);
		delete num;
		});
	parent->getEventDispatcher()->addEventListenerWithSceneGraphPriority(dieBlockListener, parent);
	
	auto damageBlockListener = EventListenerCustom::create("block_damage_event", [=](EventCustom* event) {
		Vec2* numAndDamage = static_cast<Vec2*>(event->getUserData());
		causeDamage(numAndDamage->x, numAndDamage->y);
		delete numAndDamage;
		});
	parent->getEventDispatcher()->addEventListenerWithSceneGraphPriority(damageBlockListener, parent);
}
