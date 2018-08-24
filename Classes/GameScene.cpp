#include "GameScene.h"
#include "Gold.h"
#include "Bullet.h"

USING_NS_CC;
TMXTiledMap *Game::_tileMap = nullptr;
TMXTiledMap * EnemyAI::tileMap = nullptr;
TMXLayer * EnemyAI::layer = nullptr;
Enemy * Game::enemy[10] = { NULL };
int EnemyAI::mapSizeHeight = 0;
int EnemyAI::mapSizeWidth = 0;
int EnemyAI::tileSize =0;

EnemyAI * Game::enemyAIs[10] = { nullptr };
bool Game::bVictory = false;
int Game::nEnemy = -1;
int Game::nPickup = -1;


Scene *Game::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto layer = Game::create();
	scene->addChild(layer);
	return scene;
}

bool Game::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = [](PhysicsContact & contact)
	{
		log("onContactBegin");
		auto spriteA = (Sprite *)contact.getShapeA()->getBody()->getNode();
		auto spriteB = (Sprite *)contact.getShapeB()->getBody()->getNode();
		if (spriteA && spriteB && spriteA->getTag()==3 && spriteB->getTag()==2 && spriteA->isVisible())

		{
			spriteA->setVisible(false);
			spriteB->removeFromParent();
			nEnemy--;
			log("%d",nEnemy);
		}
		else if (spriteA && spriteB && spriteA->getTag()==1 && spriteB->getTag()==6)
		{
			((PickupBase *)spriteB)->isContact((OurTank *)spriteA);
		}
		if (nEnemy == 0) {
			log("win");
		}

		return true;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);

	_tileMap = TMXTiledMap::create("map/map3.tmx");
	Bullet::_breakable0 = _tileMap->getLayer("breakable0");
	Bullet::_breakable1 = _tileMap->getLayer("breakable1");
	tileX = _tileMap->getTileSize().width;
	tileY = _tileMap->getTileSize().height;
	mapX = _tileMap->getMapSize().width;
	mapY = _tileMap->getMapSize().height;

	this->addChild(_tileMap);

	EnemyAI::tileMap = _tileMap;
	

	TMXObjectGroup *group = _tileMap->getObjectGroup("objects");
	ValueMap spawnPoint_0 = group->getObject("playerA");

	
	
	
	int  x0 = spawnPoint_0["x"].asInt();
	int  y0 = spawnPoint_0["y"].asInt();

	EnemyAI::tileMap = _tileMap;
	EnemyAI::layer = _collidable;
	EnemyAI::mapSizeHeight = _tileMap->getMapSize().height;
	EnemyAI::mapSizeWidth = _tileMap->getMapSize().width;
	EnemyAI::tileSize = _tileMap->getTileSize().width;

	ValueMap spawnPoint_3 = group->getObject("gold");
	float x3 = spawnPoint_3["x"].asFloat();
	float y3 = spawnPoint_3["y"].asFloat();

	auto gold = PickupBase::createWithType(Gold);
	gold->setPosition(Vec2(x3, y3));
	gold->setTag(6);

	_player = OurTank::createWithImage(5);
	_player->setAnchorPoint(Vec2(0.5, 0.5));
	_player->setPosition(Vec2(x0, y0));
	addChild(_player);
	this->setViewpointCenter(Vec2(x0, y0));
	//this->setPosition(Vec2(200, 200));


	/**/
	_player->addenemy();
	_player->addpickup();
	_player->setTag(1);
	_collidable = _tileMap->getLayer("collidable");
	Bullet::coll = _collidable;

	EnemyAI::layer = _collidable;

	Vec2 playerPos = _player->getPosition();

	_player->setDirection(146);

	setKeyboardEnabled(true);

	this->scheduleUpdate();


	menuLayer->runAction(MoveTo::create(0.2, -viewPoint));
	this->addChild(menuLayer);
	auto itemPause = MenuItemImage::create("UI/menu_pause.png", "UI/menu_pause1.png",
		CC_CALLBACK_1(Game::menuItemCallbackPause, this));
	itemPause->setAnchorPoint(Vec2(0, 0));
	itemPause->setPosition(Vec2(0, visibleSize.height - itemPause->getContentSize().height));
	auto menu = Menu::create(itemPause, NULL);
	menu->setPosition(Vec2::ZERO);
	menuLayer->addChild(menu);

	log("%d,%d",this->getPosition().x,this->getPosition().y);

	log("There are %d enemys ***************************", nEnemy);

	return true;
}

void Game::setPlayerPosition(Vec2 position)
{
	Size screenSize = Director::getInstance()->getVisibleSize();
	if (position.y > tileY*mapY || position.y < 0 || position.x > tileX*tileX  || position.x < 0)
	{
		return;
	}
	Vec2 tileCoord = this->tileCoordFromPosition(position);
	int tileGid = _collidable->getTileGIDAt(tileCoord);
	if (tileGid > 0) {
		Value prop = _tileMap->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();
		std::string collision = propValueMap["collidable"].asString();
		if (collision == "true") {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.mp3");
			return;
		}

	}
	_player->runAction(MoveTo::create(0.2, position));
}
Vec2 Game::tileCoordFromPosition(Vec2 pos) {
	int x = (int)pos.x / tileX;
	int y = (int)(mapY*tileY - pos.y) / tileY;
	return Vec2(x, y);
}

void Game::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	log("%d has been pressed", keyCode);
	Vec2 playerPos = _player->getPosition();
	if ((int)keyCode == 59)
	{
		_player->openFire();
		return;
	}
	if ((int)keyCode != _player->getDirection())
	{
		switch ((int)keyCode)
		{
		case 146:
			_player->runAction(RotateTo::create(0.2, 0));
			break;
		case 142:
			_player->runAction(RotateTo::create(0.2, 180));
			break;
		case 124:
			_player->runAction(RotateTo::create(0.2, 270));
			break;
		case 127:
			_player->runAction(RotateTo::create(0.2, 90));
			break;
		}
		_player->setDirection((int)keyCode);
		this->schedule(schedule_selector(Game::keepMoving), 0.2);
		return;
	}
	switch ((int)keyCode)
	{
	case 146:
		playerPos.y += _tileMap->getTileSize().height;
		break;
	case 142:
		playerPos.y -= _tileMap->getTileSize().height;
		break;
	case 124:
		playerPos.x -= _tileMap->getTileSize().width;
		break;
	case 127:
		playerPos.x += _tileMap->getTileSize().width;
		break;
	}

	if (!isMoveable(playerPos)) return;
	this->setViewpointCenter(playerPos);
	this->setPlayerPosition(playerPos);

	this->schedule(schedule_selector(Game::keepMoving), 0.2);
}

void Game::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	if((int)keyCode==_player->getDirection())
		this->unschedule(schedule_selector(Game::keepMoving));
}

void Game::keepMoving(float dt)
{
	Vec2 playerPos = _player->getPosition();
	switch (_player->getDirection())
	{
	case 146:
		playerPos.y += _tileMap->getTileSize().height;
		break;
	case 142:
		playerPos.y -= _tileMap->getTileSize().height;
		break;
	case 124:
		playerPos.x -= _tileMap->getTileSize().width;
		break;
	case 127:
		playerPos.x += _tileMap->getTileSize().width;
		break;
	}

	if (!isMoveable(playerPos)) return;
	this->setViewpointCenter(playerPos);
	this->setPlayerPosition(playerPos);

}

void Game::update(float dt)
{
	if (bVictory)
	{
		Director::getInstance()->replaceScene(HelloWorld::createScene());
	}
	for (int i = 0; enemyAIs[i]; ++i)
	{
		enemyAIs[i]->update(dt);
	}
}

void Game::menuItemCallbackPause(Ref * pSender)
{
	static bool isPause = false;
	if (!isPause)
	{
		auto layer = PauseLayer::create();
		layer->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
		Director::getInstance()->getVisibleSize().height / 2));
		layer->setTag(13);
		this->addChild(layer);
		isPause = true;
		Director::getInstance()->pause();
	}
	else
	{
		this->removeChildByTag(13);
		Director::getInstance()->resume();
		isPause = false;
	}
}

void Game::setViewpointCenter(Point position) {
	auto winSize = Director::getInstance()->getWinSize();
	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	auto mapSize = _tileMap->getMapSize();
	auto tileSize = _tileMap->getTileSize();

	x = MIN(x, mapSize.width*tileSize.width - winSize.width / 2);
	y = MIN(y, mapSize.height*tileSize.height - winSize.height / 2);

	auto centerPoint = Point(winSize.width / 2, winSize.height / 2);
	auto actualPoint = Point(x, y);
	viewPoint = centerPoint - actualPoint;


	this->runAction(MoveTo::create(0.2, viewPoint));
	log("%f,%f", this->getPosition().x, this->getPosition().y);
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	////log("%f,%f", origin.x, origin.y);
	//auto layer1 = Layer::create();
	////layer1->runAction(MoveTo::create(0.2, viewPoint));
	//auto itemPause = MenuItemImage::create("UI/menu_pause.png", "UI/menu_pause1.png",
	//	CC_CALLBACK_1(Game::menuItemCallbackPause, this));
	//itemPause->setAnchorPoint(Vec2(0, 0));
	//itemPause->setPosition(Vec2(600, 360));
	//auto menu = Menu::create(itemPause, NULL);
	//menu->setPosition(Vec2::ZERO);
	//layer1->addChild(menu);
	//this->addChild(layer1);
	menuLayer->runAction(MoveTo::create(0.2, -viewPoint));
}

bool Game::isMoveable(Vec2 position) {
	Size screenSize = Director::getInstance()->getVisibleSize();
	if (position.y > tileY*mapY  || position.y < 0 || position.x > tileX*mapX  || position.x < 0)
	{
		return false;
	}
	Vec2 tileCoord = this->tileCoordFromPosition(position);
	//log("%f, %f", tileCoord.x, tileCoord.y);
	int tileGid = _collidable->getTileGIDAt(tileCoord);
	if (tileGid > 0) {
		Value prop = _tileMap->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();
		std::string collision = propValueMap["collidable"].asString();
		if (collision == "true") {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.mp3");
			return false;
		}
	}
	return true;
}