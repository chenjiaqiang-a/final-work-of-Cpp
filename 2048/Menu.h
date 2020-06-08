#pragma once
/*
---*---�˵�������(MenuScene)---*---
�����: ������
*/
#include<easy2d/easy2d.h>
#include"MainScene.h"

using namespace easy2d;

class MenuScene : public Scene
{
private:
	Sprite* bg = nullptr;                  //����ͼƬ
	MainScene* playScene = nullptr;        //��Ϸ����
	Button* startButton = nullptr;         //��ʼ��ť
public:
	MenuScene();
	void start();
};

//���캯��
MenuScene::MenuScene()
{
	playScene = gcnew MainScene;                               //�����Ϸ����
	this->addChild(playScene);
	playScene->setVisible(false);

	bg = gcnew Sprite(L"./image/menubg.png");                  //��ӱ���ͼƬ
	bg->setPos(0, 0);
	this->addChild(bg);

	auto startpic = gcnew Sprite(L"./image/startButton.png");  //��ӿ�ʼ��Ϸ��ť
	startButton = gcnew Button(startpic);
	startButton->setAnchor(0.5, 0.5);
	startButton->setPos(Window::getWidth() / 2, Window::getHeight() / 2);
	bg->addChild(startButton);

	auto func = std::bind(&MenuScene::start, this);            //���ð�ť����
	startButton->setClickFunc(func);
}

//�����ʼ��Ϸ��ť, ����start����, ������Ϸ������ʼ��Ϸ
void MenuScene::start() 
{
	playScene->setVisible(true);
	SceneManager::enter(playScene);
	playScene->start();
};