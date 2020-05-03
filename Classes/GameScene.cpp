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
	return true;
}

void GameScene::createHeader()
{
	auto headerNode = Node::create();
	headerNode->setContentSize(Size(visibleSize.width,HEADER_HEIGHT));
	headerNode->setAnchorPoint(Point(0,0));
	headerNode->setPosition(origin.x,origin.y + visibleSize.height - HEADER_HEIGHT);
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
	auto edgeBody = PhysicsBody::createEdgeBox(edgeSize, PhysicsMaterial(0, 1, 0), 5);
	edgeBody->setCollisionBitmask(EDGE_MASK);
	edgeBody->setContactTestBitmask(true);
	edgeNode->setPhysicsBody(edgeBody);

	// Create ceiling
	auto ceiling = Sprite::create();
	ceiling->setTextureRect(Rect(Vec2(0, 0), ceilingSize));
	ceiling->setColor(Color3B::GRAY);
	ceiling->setPosition(0, edgeSize.height / 2 - ceilingSize.height / 2);
	auto ceilingBody = PhysicsBody::createEdgeBox(ceilingSize, PhysicsMaterial(0, 1, 0), 1);
	ceilingBody->setCollisionBitmask(CEILING_MASK);
	ceilingBody->setContactTestBitmask(true);
	ceiling->setPhysicsBody(ceilingBody);

	// Create footer
	auto footer = Sprite::create();
	footer->setTextureRect(Rect(Vec2(0, 0), footerSize));
	footer->setColor(Color3B::GREEN);
	footer->setPosition(0, -(edgeSize.height / 2 - footerSize.height / 2));
	auto footergBody = PhysicsBody::createEdgeBox(footerSize, PhysicsMaterial(0, 1, 0), 1);
	footergBody->setCollisionBitmask(FOOTER_MASK);
	footergBody->setContactTestBitmask(true);
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
	player = new Player(arena,header);
}
