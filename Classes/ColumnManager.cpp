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
	addListeners();
}

ColumnManager::~ColumnManager()
{
	releaser->release();
}

void ColumnManager::adjustImagesToColumnNumber(int columnNubmer)
{
	const Size oneThirdSize = Size((columnWidth - ICICLE_PADDING)/3, (columnWidth - ICICLE_PADDING) / 3);
	const Size twoThirdSize = Size(oneThirdSize.width * 2, oneThirdSize.height * 2);
	const Size threeThirdSize = Size(oneThirdSize.width * 3, oneThirdSize.height * 3);

	ImageManager::instance().addTexture(ICICLE_IMAGE, oneThirdSize);
	ImageManager::instance().addTexture(ICICLE_SECOND_IMAGE, twoThirdSize);
	ImageManager::instance().addTexture(ICICLE_THIRD_IMAGE, threeThirdSize);

	ImageManager::instance().addTexture(SPIDER_IMAGE, Size(columnWidth - SPIDER_PADDING, columnWidth - SPIDER_PADDING));
	ImageManager::instance().addTexture(SPIDER_DEAD_IMAGE, Size(columnWidth - SPIDER_PADDING, columnWidth - SPIDER_PADDING));
	ImageManager::instance().addTexture(FRAGMENT_IMAGE, FRAGMENT_SIZE);
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

void ColumnManager::addListeners()
{
	auto _listener2 = EventListenerCustom::create("release_column_event", [=](EventCustom* event) {

		int* column = static_cast<int*>(event->getUserData());
		releaseColumn(*column);
		delete column;
		return true;
		});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener2, releaser);
}
