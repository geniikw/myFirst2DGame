#include"basicScene.h"

CCScene* basicScene::scene()
{
	CCScene *pScene = CCScene::node();
	basicScene *pLayer = basicScene::node();

	pScene->addChild(pLayer);

	return pScene;
}

bool basicScene::init()
{
	if (!CCLayer::init()) return false;

	this->schedule(schedule_selector(basicScene::tick));
	return true;
}

void basicScene::tick(ccTime dt)
{

}