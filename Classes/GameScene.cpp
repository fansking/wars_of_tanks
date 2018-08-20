#include "SimpleAudioEngine.h"
#include "GameScene.h"

USING_NS_CC;
Scene *Game::createScene()
{
	auto scene = Scene::create();
	auto layer = Game::create();
	scene->addChild(layer);
	return scene;
}
bool Game::onTouchBegan(Touch* touch, Event * event)
{
	log("onTouchBegan");
	return true;
}
void Game::onTouchMoved(Touch* touch, Event * event)
{
	log("onTouchMoved");
}
void Game::onTouchEnded(Touch* touch, Event * event)
{
	log("onTouchEnded");
	Vec2 touchLocation = touch->getLocation();
	Vec2 playerPos = _player->getPosition();
	Vec2 diff = touchLocation - playerPos;

	if (abs(diff.x) > abs(diff.y))
	{
		if (diff.x>0)
		{
			playerPos.x += _tileMap->getTileSize().width;
		}
		else
		{
			playerPos.x -= _tileMap->getTileSize().width;
		}
	}
	else {
		if (diff.y > 0)
		{
			playerPos.y += _tileMap->getTileSize().height;
		}
		else
		{
			playerPos.y -= _tileMap->getTileSize().height;
		}
	}
	this->runAction(MoveTo::create(5, playerPos));
}
void Game::setPlayerPosition(Vec2 position)
{
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
	Size screenSize = Director::getInstance()->getVisibleSize();
	if (position.y >= screenSize.height || position.y <= 0 || position.x >= screenSize.width || position.x <= 0)
	{
		return;
	}
	_player->runAction(MoveTo::create(0.1, position));
}
Vec2 Game::tileCoordFromPosition(Vec2 pos) {
	int x = pos.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - pos.y) / _tileMap->getTileSize().height;
	return Vec2(x, y);
}

bool Game::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_tileMap = TMXTiledMap::create("map/map2.tmx");
	_tileMap->setScale(Director::getInstance()->getVisibleSize().width / (_tileMap->getMapSize().width * _tileMap->getTileSize().width));
	this->addChild(_tileMap);

	TMXObjectGroup *group = _tileMap->getObjectGroup("objects");
	ValueMap spawnPoint = group->getObject("ninja");

	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

	_player = OurTank::createWithImage(5);
	_player->setAnchorPoint(Vec2(0.5, 0.5));
	_player->setPosition(Vec2(x, y));
	addChild(_player, 2, 200);
	_collidable = _tileMap->getLayer("collidable");

	_player->setDirection(146);

	/*setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	setKeypadEnabled(true);*/

	setKeyboardEnabled(true);

	return true;
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
		this->schedule(schedule_selector(Game::keepMoving), 0.1f);
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
	this->setPlayerPosition(playerPos);

	this->schedule(schedule_selector(Game::keepMoving), 0.1f);
}

void Game::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	this->unscheduleAllSelectors();
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
	this->setPlayerPosition(playerPos);

}