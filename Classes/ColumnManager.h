#pragma once
#include "settings.h"
#include "definitions.h"
#include "cocos2d.h"
#include "ImageManager.h"
#include <vector>

struct Column
{
	int number = -1;
	int centerPosition = -1;
};

class ColumnManager
{
public:
	ColumnManager(cocos2d::Node* _parent, int _columnCount);
	~ColumnManager();
	void adjustImagesToColumnNumber(int columnNubmer);
	Column getFreeColumn();
	void releaseColumn(int columnNumber);
	void releaseColumnAfter(int columnNumber, float time);

private:
	cocos2d::Node* parent;
	cocos2d::Sprite* releaser;
	std::vector<bool> columns;
	int columnCount;
	int arenaWidth;
	int columnWidth;
};

