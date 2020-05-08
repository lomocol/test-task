#include "BonusSpawner.h"

using namespace std;
using namespace cocos2d;

BonusSpawner::BonusSpawner(cocos2d::Node* _parent, int maxMonsterCount) :
	iSpawner(_parent, maxMonsterCount)
{
	addListeners();
}


void BonusSpawner::dropSpiderBonus(cocos2d::Vec2 position)
{
	BonusType type = randomBonusType(icicleBonus);
	//if (type == BonusType::Empty) {
	if (true) {
		EffectMaker::instance().dropDefaultEfffect(parent,position,EffectType::Fire,ICICLE_DIE_EFFECT_DURATION);
	}
	else {
		
	}
}

void BonusSpawner::dropIcicleBonus(cocos2d::Vec2 position)
{
	BonusType type = randomBonusType(icicleBonus);
	//if (type == BonusType::Empty) {
	if (true) {
		EffectMaker::instance().dropFragments(parent, position);
	}
	else {
		
	}
}



void BonusSpawner::addListeners()
{
	auto dropSpiderListener = EventListenerCustom::create("spider_drop_bonus_event", [=](EventCustom* event) {
		Vec2 * position = static_cast<Vec2*>(event->getUserData());
		dropSpiderBonus(*position);
		delete position;
		});
	parent->getEventDispatcher()->addEventListenerWithSceneGraphPriority(dropSpiderListener, parent);
	
	auto dropIcicleListener = EventListenerCustom::create("icicle_drop_bonus_event", [=](EventCustom* event) {
		Vec2 * position = static_cast<Vec2*>(event->getUserData());
		dropIcicleBonus(*position);
		delete position;
		});
	parent->getEventDispatcher()->addEventListenerWithSceneGraphPriority(dropIcicleListener, parent);
}

BonusType BonusSpawner::randomBonusType(const std::vector<BonusType> & types)
{
	bool bonusWillBe = rand() % 100 < BONUS_CHANCE;
	if (bonusWillBe)
	{
		int bonusNum = rand() % types.size();
		return types[bonusNum];
	}
	else
		return BonusType::Empty;
}
