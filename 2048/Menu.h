#pragma once
#include<easy2d/easy2d.h>
#include"MainScene.h"
using namespace easy2d;
class MenuScene : public Scene
{
private:
	Sprite* bg = nullptr; //±³¾°Í¼Æ¬
	MainScene* playScene = nullptr;
	Button* startButton = nullptr;
public:
	MenuScene();
	void start();
};
MenuScene::MenuScene() {
	playScene = gcnew MainScene;
	this->addChild(playScene);
	playScene->setVisible(false);
	bg = gcnew Sprite(L"./image/menubg.png");
	bg->setPos(0, 0);
	this->addChild(bg);

	auto startpic = gcnew Sprite(L"./image/startButton.png");
	startButton = gcnew Button(startpic);
	startButton->setAnchor(0.5, 0.5);
	startButton->setPos(Window::getWidth() / 2, Window::getHeight() / 2);
	bg->addChild(startButton);
	auto func = std::bind(&MenuScene::start, this);
	startButton->setClickFunc(func);
}
void MenuScene::start() {
	playScene->setVisible(true);
	SceneManager::enter(playScene);
	playScene->start();
};