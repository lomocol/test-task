#pragma once
#include "iSpawner.h"
#include "../monsters/block.h"

class BlockSpawner :
	public iSpawner
{
public:
	BlockSpawner(cocos2d::Node* _parent, int maxMonsterCount);
	void spawn(cocos2d::Vec2 position);
private:
	void addListeners();
	void spawn() override {};
};

