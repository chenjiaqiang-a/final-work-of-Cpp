#pragma once
/*
---*---菜单场景类(MenuScene)---*---
完成者: 尹子鳗
*/
#include<easy2d/easy2d.h>
#include"MainScene.h"

using namespace easy2d;

class MenuScene : public Scene
{
private:
	Sprite* bg = nullptr;                  //背景图片
	MainScene* playScene = nullptr;        //游戏场景
	Button* startButton = nullptr;         //开始按钮
public:
	MenuScene();
	void start();
};

//构造函数
MenuScene::MenuScene()
{
	playScene = gcnew MainScene;                               //添加游戏场景
	this->addChild(playScene);
	playScene->setVisible(false);

	bg = gcnew Sprite(L"./image/menubg.png");                  //添加背景图片
	bg->setPos(0, 0);
	this->addChild(bg);

	auto startpic = gcnew Sprite(L"./image/startButton.png");  //添加开始游戏按钮
	startButton = gcnew Button(startpic);
	startButton->setAnchor(0.5, 0.5);
	startButton->setPos(Window::getWidth() / 2, Window::getHeight() / 2);
	bg->addChild(startButton);

	auto func = std::bind(&MenuScene::start, this);            //设置按钮函数
	startButton->setClickFunc(func);
}

//点击开始游戏按钮, 调用start函数, 进入游戏场景开始游戏
void MenuScene::start() 
{
	playScene->setVisible(true);
	SceneManager::enter(playScene);
	playScene->start();
};