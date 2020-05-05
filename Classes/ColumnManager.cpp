#include "ColumnManager.h"

using namespace std;
using namespace cocos2d;

ColumnManager::ColumnManager(cocos2d::Node* _parent,int _arenaWidth, int _columnCount) :arenaWidth(_arenaWidth), 
columnCount(_columnCount), parent(_parent)
{
	releaser = Sprite::create();
	parent->addChild(releaser);
	columnWidth = arenaWidth / columnCount;
	columns.assign(columnCount, false);
}

ColumnManager::~ColumnManager()
{
	releaser->release();
}

Column ColumnManager::getFreeColumn()
{
	vector<int> numbers;
	for (size_t i = 0; i < columnCount; i++)
	{
		if (columns[i] == false)
			numbers.push_back(i);
	}

	if (numbers.size() == 0)
		return {-1,-1};

	int columnNumber = numbers[rand() % numbers.size()];
	int position = columnNumber * columnWidth + columnWidth / 2;

	columns[columnNumber] = true;

	return { columnNumber , position };
}

void ColumnManager::releaseColumn(int columnNumber)
{
	columns[columnNumber] = false;
}

void ColumnManager::releaseColumnAfter(int columnNumber, float time)
{
	auto releaseAction = CallFunc::create([this, columnNumber]() {releaseColumn(columnNumber);});
	auto delay = DelayTime::create(time);
	auto sequence = Sequence::create(delay,releaseAction,nullptr);
	releaser->runAction(sequence);
}
