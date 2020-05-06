#include "GameScene.h"

using namespace cocos2d;
using namespace ui;
using namespace std;

cocos2d::Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	scene->getPhysicsWorld()->setGravity(NORMAL_GRAVITY);
	auto layer = GameScene::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());

	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	createGameSurface();
	createHeader();
	createPlayer();

	initManagers();
	startIcicleSpawn();
	startSpiderSpawn();
	addListeners();

	return true;
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	auto one = a->getTag();
	auto two = b->getTag();

	
	if (one == PLAYER_TAG || two == PLAYER_TAG)
	{
		one == PLAYER_TAG ? contactWithPlayer(two) : contactWithPlayer(one);
		return true;
	}
	if (IS_ICICLE(one) || IS_ICICLE(two))
	{
		IS_ICICLE(one) ? contactWithIcicle(one, two) : contactWithIcicle(two, one);
		return true;
	}
	if (IS_SPIDER(one) || IS_SPIDER(two))
	{
		IS_SPIDER(one) ? contactWithSpider(one, two) : contactWithSpider(two, one);
		return true;
	}

	return true;
}

void GameScene::createHeader()
{
	auto headerNode = Node::create();
	headerNode->setContentSize(Size(visibleSize.width, HEADER_HEIGHT));
	headerNode->setAnchorPoint(Point(0, 0));
	headerNode->setPosition(origin.x, origin.y + visibleSize.height - HEADER_HEIGHT);
	this->addChild(headerNode);
	header = new Header(headerNode);
}

void GameScene::createGameSurface()
{
	Size edgeSize(visibleSize.width, visibleSize.height - HEADER_HEIGHT);
	Size ceilingSize(visibleSize.width, 30);
	Size footerSize(visibleSize.width, 30);
	Size arenaSize(edgeSize.width, edgeSize.height - ceilingSize.height - footerSize.height);

	// Create edgeBox
	auto edgeNode = Node::create();
	edgeNode->setPosition(visibleSize.width / 2 + origin.x, (visibleSize.height - HEADER_HEIGHT) / 2 + origin.y);
	auto edgeBody = PhysicsBody::createEdgeBox(edgeSize, PHYSICSBODY_MATERIAL_DEFAULT, 5);
	setBodyInfo(edgeBody, EDGE_BODY_INFO);
	edgeNode->setPhysicsBody(edgeBody);

	// Create ceiling
	auto ceiling = Sprite::create();
	ceiling->setTextureRect(Rect(Vec2(0, 0), ceilingSize));
	ceiling->setColor(Color3B::GRAY);
	ceiling->setPosition(0, edgeSize.height / 2 - ceilingSize.height / 2);
	auto ceilingBody = PhysicsBody::createEdgeBox(ceilingSize, PhysicsMaterial(0, 1, 0), 1);
	setBodyInfo(ceilingBody, CEILING_BODY_INFO);
	ceilingBody->setDynamic(false);
	ceiling->setPhysicsBody(ceilingBody);

	// Create footer
	auto footer = Sprite::create();
	footer->setTextureRect(Rect(Vec2(0, 0), footerSize));
	footer->setColor(Color3B::GREEN);
	footer->setPosition(0, -(edgeSize.height / 2 - footerSize.height / 2));
	auto footergBody = PhysicsBody::createEdgeBox(footerSize, PHYSICSBODY_MATERIAL_DEFAULT, 1);
	setBodyInfo(footergBody, FOOTER_BODY_INFO);
	ceilingBody->setDynamic(false);
	footer->setPhysicsBody(footergBody);

	// Create arena
	arena = Node::create();
	arena->setAnchorPoint(Point(0, 0));
	arena->setContentSize(arenaSize);
	arena->setPosition(-(edgeSize.width / 2), footerSize.height - edgeSize.height / 2);

	// Create background
	auto background = Sprite::create();
	background->setTextureRect(Rect(Vec2(0, 0), arenaSize));
	background->setColor(Color3B::YELLOW);
	background->setAnchorPoint({ 0,0 });
	background->setPosition({ 0,0 });

	arena->addChild(background);
	edgeNode->addChild(ceiling);
	edgeNode->addChild(footer);
	edgeNode->addChild(arena);

	this->addChild(edgeNode);

}

void GameScene::createPlayer()
{
	ImageManager::instance().addTexture(PLAYER_IMAGE, PLAYER_SIZE);

	Vec2 position(visibleSize.width / 2, visibleSize.height / 2);

	player = new Player(PLAYER_IMAGE, arena, header, position, PLAYER_BODY_INFO);
}

void GameScene::addListeners()
{
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void GameScene::startIcicleSpawn()
{
	icicleSpawner->startSpawn();
}

void GameScene::startSpiderSpawn()
{
	spiderSpawner->startSpawn();

}

void GameScene::initManagers()
{
	columnManager = new ColumnManager(arena, COLUMN_COUNT);

	icicleSpawner = new IcicleSpawner(arena, columnManager, MAX_ICICLE_COUNT_FROM);
	spiderSpawner = new SpiderSpawner(arena, columnManager, MAX_SPIDER_COUNT_FROM);
}

void GameScene::contactWithPlayer(int contactorTag)
{
	if (IS_ICICLE(contactorTag))
	{
		player->causeDomage(50);
		contactWithIcicle(contactorTag,PLAYER_TAG);
	}
}

void GameScene::contactWithIcicle(int icicleTag, int contactorTag)
{
	if (contactorTag == FOOTER_TAG)
	{
		icicleSpawner->destroyIcicle(icicleTag);
	}
	if (contactorTag == PLAYER_TAG)
	{
		icicleSpawner->destroyIcicle(icicleTag,true);
	}
}

void GameScene::contactWithSpider(int spiderTag, int contactorTag)
{
}
