#include "BonusSpawner.h"

using namespace std;
using namespace cocos2d;

BonusSpawner::BonusSpawner(cocos2d::Node* _parent, int maxMonsterCount) :
	iSpawner(_parent, maxMonsterCount)
{
	typeFileNames.insert(std::pair<BonusType, const string>(BonusType::Block, BLOCK_IMAGE));
	typeFileNames.insert(std::pair<BonusType, const string>(BonusType::Shield, SHIELD_IMAGE));
	typeFileNames.insert(std::pair<BonusType, const string>(BonusType::FireBall, FIREBALL_IMAGE));
	typeFileNames.insert(std::pair<BonusType, const string>(BonusType::Health, HEALTH_IMAGE));
	typeFileNames.insert(std::pair<BonusType, const string>(BonusType::Protection, PROTECTION_IMAGE));

	addListeners();
}


void BonusSpawner::dropSpiderBonus(const cocos2d::Vec2& position)
{
	BonusType type = randomBonusType(icicleBonus);
	if (type == BonusType::Empty) {
		EffectMaker::instance().dropDefaultEfffect(parent, position, EffectType::Fire, ICICLE_DIE_EFFECT_DURATION);
	}
	else {
		spawn(type, position);
	}
}

void BonusSpawner::dropIcicleBonus(const cocos2d::Vec2& position)
{
	BonusType type = randomBonusType(icicleBonus);
	if (type == BonusType::Empty) {
		EffectMaker::instance().dropFragments(parent, position);
	}
	else {
		spawn(type, position);
	}
}

void BonusSpawner::addListeners()
{
	auto dropSpiderListener = EventListenerCustom::create("spider_drop_bonus_event", [=](EventCustom* event) {
		Vec2* position = static_cast<Vec2*>(event->getUserData());
		dropSpiderBonus(*position);
		delete position;
		});
	parent->getEventDispatcher()->addEventListenerWithSceneGraphPriority(dropSpiderListener, parent);

	auto dropIcicleListener = EventListenerCustom::create("icicle_drop_bonus_event", [=](EventCustom* event) {
		Vec2* position = static_cast<Vec2*>(event->getUserData());
		dropIcicleBonus(*position);
		delete position;
		});
	parent->getEventDispatcher()->addEventListenerWithSceneGraphPriority(dropIcicleListener, parent);

	auto dieBonusListener = EventListenerCustom::create("bonus_die_event", [=](EventCustom* event) {
		int* num = static_cast<int*>(event->getUserData());
		releaseMonster(*num);
		delete num;
		});
	parent->getEventDispatcher()->addEventListenerWithSceneGraphPriority(dieBonusListener, parent);
}

BonusType BonusSpawner::randomBonusType(const std::vector<BonusType>& types)
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

void BonusSpawner::spawn(BonusType type, const cocos2d::Vec2 position)
{
	int spriteNumber = getFreeMonsterNumber();

	if (spriteNumber != -1)
	{
		BodyInfo bodyInfo = BONUS_BODY_INFO;
		bodyInfo.tag += spriteNumber;
		Bonus* bonus = new Bonus(typeFileNames[type], parent, position, bodyInfo, type);
		monsters[spriteNumber] = bonus;
	}
	else
		EffectMaker::instance().dropDefaultEfffect(parent, position, EffectType::Space, ICICLE_DIE_EFFECT_DURATION);
}


void BonusSpawner::removeBonus(int bonusTag)
{
	auto bonus = monsters[bonusTag];
	if (bonus != nullptr)
	{
		bonus->die();
		delete bonus;
		monsters[bonusTag] = nullptr;
	}
}