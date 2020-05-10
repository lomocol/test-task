#include "GameScene.h"
#include "iostream"

using namespace cocos2d;
using namespace ui;
using namespace std;

cocos2d::Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	auto world = scene->getPhysicsWorld();
	world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	scene->getPhysicsWorld()->setGravity(NORMAL_GRAVITY);
	auto layer = GameScene::create();

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


	this->scheduleUpdate();

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
	Size ceilingSize(visibleSize.width, CEILING_HEIGHT);
	Size footerSize(visibleSize.width, FOOTER_HEIGHT);
	Size arenaSize(edgeSize.width, edgeSize.height - ceilingSize.height - footerSize.height);

	ImageManager::instance().addTexture(BACKGROUND_IMAGE, arenaSize);
	ImageManager::instance().addTexture(FOOTER_IMAGE, footerSize);
	ImageManager::instance().addTexture(CEILING_IMAGE, ceilingSize);

	// Create edgeBox
	auto edgeNode = Node::create();
	edgeNode->setPosition(visibleSize.width / 2 + origin.x, (visibleSize.height - HEADER_HEIGHT) / 2 + origin.y);
	auto edgeBody = PhysicsBody::createEdgeBox(edgeSize, PHYSICSBODY_MATERIAL_DEFAULT, 5);
	setBodyInfo(edgeBody, EDGE_BODY_INFO);
	edgeNode->setPhysicsBody(edgeBody);

	// Create ceiling
	auto ceilingTexture = ImageManager::instance().getTexture(CEILING_IMAGE);
	auto ceiling = Sprite::createWithTexture(ceilingTexture);
	ceiling->setPosition(0, edgeSize.height / 2 - ceilingSize.height / 2);
	auto ceilingBody = PhysicsBody::createEdgeBox(ceilingSize, PhysicsMaterial(0, 1, 0), 1);
	setBodyInfo(ceilingBody, CEILING_BODY_INFO);
	ceilingBody->setDynamic(false);
	ceiling->setPhysicsBody(ceilingBody);

	// Create footer
	auto footerTexture = ImageManager::instance().getTexture(FOOTER_IMAGE);
	auto footer = Sprite::createWithTexture(footerTexture);
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
	auto backgroundTexture = ImageManager::instance().getTexture(BACKGROUND_IMAGE);
	auto background = Sprite::createWithTexture(backgroundTexture);
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
	shotSpawner = new ShotSpawner(arena, player->getSprite(), MAX_SHOT_COUNT_FROM);
	bonusSpawner = new BonusSpawner(arena, BONUS_MAX_COUNT);
	player->setShotSpiwner(shotSpawner);
}


void GameScene::update(float dt)
{
	DynamicCreator::instance().createSprites();
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
	PhysicsBody* oneBody = contact.getShapeA()->getBody();
	PhysicsBody* twoBody = contact.getShapeB()->getBody();

	auto oneTag = oneBody->getTag();
	auto twoTag = twoBody->getTag();


	if (oneTag == PLAYER_TAG || twoTag == PLAYER_TAG)
	{
		oneTag == PLAYER_TAG ? contactWithPlayer(twoTag, twoBody) : contactWithPlayer(oneTag, oneBody);
		return true;
	}
	if (IS_FRAGMENT(oneTag) || IS_FRAGMENT(twoTag))
	{
		IS_FRAGMENT(oneTag) ? contactWithFragment(oneBody, twoTag) : contactWithFragment(twoBody, oneTag);
		return true;
	}
	if (IS_SHOT(oneTag) || IS_SHOT(twoTag))
	{
		IS_SHOT(oneTag) ? contactWithShot(oneTag, twoTag) : contactWithShot(twoTag, oneTag);
		return true;
	}
	if (IS_ICICLE(oneTag) || IS_ICICLE(twoTag))
	{
		IS_ICICLE(oneTag) ? contactWithIcicle(oneTag, twoTag) : contactWithIcicle(twoTag, oneTag);
		return true;
	}
	if (IS_SPIDER(oneTag) || IS_SPIDER(twoTag))
	{
		IS_SPIDER(oneTag) ? contactWithSpider(oneTag, twoTag) : contactWithSpider(twoTag, oneTag);
		return true;
	}
	if (IS_BONUS(oneTag) || IS_BONUS(twoTag))
	{
		IS_BONUS(oneTag) ? contactWithBonus(oneTag, twoTag) : contactWithBonus(twoTag, oneTag);
		return true;
	}
	return true;
}

void GameScene::contactWithPlayer(int contactorTag, cocos2d::PhysicsBody* contactorBody)
{
	
 	if (IS_ICICLE(contactorTag))
	{
		float verticalVelosity = -contactorBody->getVelocity().y;

		player->causeDamage(verticalVelosity * DAMAGE_FROM_ICICLE * PLAYER_DAMAGE_COEFFICIENT);
		contactWithIcicle(contactorTag, PLAYER_TAG);
		return;
	}
	if (IS_SHOT(contactorTag))
	{
		player->causeDamage(DAMAGE_FROM_SHOT * PLAYER_DAMAGE_COEFFICIENT);
		shotSpawner->removeShot(contactorTag - SHOT_TAG);
		return;
	}
	if (IS_SPIDER(contactorTag))
	{
		player->causeDamage(DAMAGE_FROM_SPIDER * PLAYER_DAMAGE_COEFFICIENT);
		spiderSpawner->causeDamage(contactorTag - SPIDER_TAG, 0);
		return;
	}
	if (IS_FRAGMENT(contactorTag))
	{
		player->causeDamage(DAMAGE_FROM_FRAGMENT * PLAYER_DAMAGE_COEFFICIENT);
		contactorBody->getOwner()->removeFromParent();
		return;
	}
	if (IS_BONUS(contactorTag))
	{
		bonusSpawner->removeBonus(contactorTag - BONUS_TAG);
		return;
	}
}

void GameScene::contactWithIcicle(int icicleTag, int contactorTag)
{
	if (contactorTag == FOOTER_TAG)
	{
		icicleSpawner->causeDamage(icicleTag - ICICLE_TAG, ICICLE_HEALTH);
	}
	if (contactorTag == PLAYER_TAG)
	{
		icicleSpawner->causeDamage(icicleTag - ICICLE_TAG, ICICLE_HEALTH);
	}
	if (IS_BONUS(contactorTag))
	{
		icicleSpawner->causeDamage(icicleTag - ICICLE_TAG, ICICLE_HEALTH);
		bonusSpawner->removeBonus(contactorTag - BONUS_TAG);
	}
}

void GameScene::contactWithSpider(int spiderTag, int contactorTag)
{
	if (contactorTag == FOOTER_TAG)
	{
		spiderSpawner->causeDamage(spiderTag - SPIDER_TAG, 0);
	}
}

void GameScene::contactWithShot(int shotTag, int contactorTag)
{
	if (IS_SPIDER(contactorTag)) {
		spiderSpawner->causeDamage(contactorTag - SPIDER_TAG, DAMAGE_FROM_SHOT * 50);
		shotSpawner->removeShot(shotTag - SHOT_TAG);
		return;
	}
	if (IS_ICICLE(contactorTag)) {

		icicleSpawner->causeDamage(contactorTag - ICICLE_TAG, DAMAGE_FROM_SHOT * 150);
		shotSpawner->removeShot(shotTag - SHOT_TAG);
		return;
	}
	if (contactorTag == CEILING_TAG || contactorTag == FOOTER_TAG)
		shotSpawner->removeShot(shotTag - SHOT_TAG);
}

void GameScene::contactWithFragment(cocos2d::PhysicsBody* fragmentBody, int contactorTag)
{
	auto owner = fragmentBody->getOwner();
	if (owner != nullptr)
		owner->removeFromParent();
	if (IS_SHOT(contactorTag))
	{
		shotSpawner->removeShot(contactorTag - SHOT_TAG);
	}
}

void GameScene::contactWithBonus(int bonusTag, int contactorTag)
{

	if (contactorTag == CEILING_TAG || contactorTag == EDGE_TAG)
	{
		bonusSpawner->removeBonus(bonusTag - BONUS_TAG);
		return;
	}
	
}
