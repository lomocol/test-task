#pragma once
#include "cocos2d.h"
#include "definitions.h"
#include "settings.h"
#include "ColumnManager.h"
#include "iSpawner.h"
#include "icicle.h"

class IcicleSpawner : public iSpawner
{
public:
	IcicleSpawner(cocos2d::Node* _parent, ColumnManager* columnManager, int maxMonsterCount);
	void startSpawn() override;

private:
	void spawn() override;

};