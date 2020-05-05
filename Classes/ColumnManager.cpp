#include "ColumnManager.h"

using namespace std;
using namespace cocos2d;

ColumnManager::ColumnManager(cocos2d::Node* _parent, int _columnCount) : columnCount(_columnCount), parent(_parent)
{
	arenaWidth = parent->getContentSize().width;
	releaser = Sprite::create();
	parent->addChild(releaser);
	columnWidth = arenaWidth / columnCount;
	columns.assign(columnCount, false);
	adjustImagesToColumnNumber(columnCount);
}

ColumnManager::~ColumnManager()
{
	releaser->release();
}

void ColumnManager::adjustImagesToColumnNumber(int columnNubmer)
{
	ImageManager::instance().addTexture(ICICLE_IMAGE, Size(columnWidth - ICICLE_PADDING, 30));
	ImageManager::instance().addTexture(ICICLE_SECOND_IMAGE, Size(columnWidth - ICICLE_PADDING, 45));
	ImageManager::instance().addTexture(ICICLE_THIRD_IMAGE, Size(columnWidth - ICICLE_PADDING, 55));

	ImageManager::instance().addTexture(SPIDER_IMAGE, Size(columnWidth - SPIDER_PADDING, columnWidth - SPIDER_PADDING));
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
		return { -1,-1 };

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
	auto sequence = Sequence::create(delay, releaseAction, nullptr);
	releaser->runAction(sequence);
}
