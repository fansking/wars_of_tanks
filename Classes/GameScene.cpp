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
	Vec2 diff = touchLocation-playerPos;

	if (abs(diff.x) > abs(diff.y))
	{
		if(diff.x>0)
		{
		playerPos.x += _tileMap->getTileSize().width;
		_player->runAction(FlipX::create(false));
		}
		else 
		{
			playerPos.x -= _tileMap->getTileSize().width;
			_player->runAction(FlipX::create(true));
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
	this->setPlayerPosition(playerPos);
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
	_player->setPosition(position);
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
	this->addChild(_tileMap);
	

	 TMXObjectGroup *group = _tileMap->getObjectGroup("objects");
	ValueMap spawnPoint = group->getObject("ninja");

	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

	_player = Sprite::create("map/ninja.png");
	_player->setPosition(Vec2(x, y));
	addChild(_player,2,200); 
	_collidable = _tileMap->getLayer("collidable");


	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	setKeypadEnabled(true);
	return true;
}