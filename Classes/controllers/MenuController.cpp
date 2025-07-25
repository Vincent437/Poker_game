#include "MenuController.h"
#include "views/scene/LevelSelectScene.h"
//#include "views/scenes/GameScene.h" // ��������һ������

MenuController::MenuController(cocos2d::Scene* parentScene) : _parentScene(parentScene) {}

void MenuController::onStartButtonClicked() {
    // ʾ�����л�����Ϸ������ҵ���߼���
    /*auto gameScene = GameScene::create();
    Director::getInstance()->replaceScene(gameScene);*/
    auto levelSelectScene = LevelSelectScene::create();
    cocos2d::Director::getInstance()->replaceScene(levelSelectScene);
    // �����߼����粥����Ч���������ݵȣ�
    // AudioEngine::playEffect("click.mp3");
}


void MenuController::menuCloseCallback()
{
    //Close the cocos2d-x game scene and quit the application
    cocos2d::Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
