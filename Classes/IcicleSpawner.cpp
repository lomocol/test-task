#include "IcicleSpawner.h"

using namespace std;
using namespace cocos2d;

IcicleSpawner::IcicleSpawner(cocos2d::Node* _parent)
{
	parent = _parent;
	arenaSize = parent->getContentSize();
}

void IcicleSpawner::startSpawn()
{
	int max_icicle_count = 10;
	icicles.assign(max_icicle_count, nullptr);

	spawner = Sprite::create();
	auto callback = CallFunc::create([this]() {this->spawnIcicle();});
	auto sequense = Sequence::create(callback, nullptr);

	parent->addChild(spawner);
	spawner->runAction(sequense);
}

void IcicleSpawner::spawnIcicle()
{

	int num = -1;
	for (int i = 0; i < icicles.size(); i++)
		if (icicles[i] == nullptr)
		{
			num = i;
			break;
		}

	if (num != -1)
	{
		Icicle* ice = new Icicle(Vec2(2, 2), num + 1);
		auto ice_sprite = ice->getSprite();
		int x = rand() % static_cast<int>(arenaSize.width - ice_sprite->getContentSize().width / 2) + ice_sprite->getContentSize().width / 2;
		ice_sprite->setPosition(x, arenaSize.height - 10 - ice_sprite->getContentSize().height / 2);

		parent->addChild(ice_sprite);
		ice->fall();
		icicles[num] = ice;
	}


	auto delay = DelayTime::create(0.55);
	auto callback = CallFunc::create([this]() {this->spawnIcicle();});

	auto sequense = Sequence::create(delay, callback, nullptr);
	spawner->runAction(sequense);
}