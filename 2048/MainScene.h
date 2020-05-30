#pragma once
#include <easy2d/easy2d.h>
#include <random>
#include <vector>
#include "2Dmatrix.h"
#include "brick.h"

using namespace easy2d;

class MainScene : public Scene
{
private:
	Matrix<Point>* pos;
	Matrix<int>* num;
	Matrix<Brick* >* bricks;
	Button* startButton = nullptr;
	Button* replayButton = nullptr;
public:
	MainScene();
	void start();          //点击"开始游戏"或"再来一局",执行strat进行场景初始化
	void clear();          //清楚上次游戏的痕迹
	void newBrick();       //在空白位子随机产生一个brick
	//-----玩家操作-----
	void pressLeft();
	void pressRight();
	void pressUp();
	void PressDown();
	//------------------
	bool isGameOver();     //判断是否游戏结束
	void end();            //一场游戏结束后调用end
	void onUpdate();       //事件循环,处理玩家命令
};

MainScene::MainScene()
{
	pos = gcnew Matrix<Point>(4, 4);
	num = gcnew Matrix<int>(4, 4);
	bricks = gcnew Matrix<Brick*>(4, 4);
	for(int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
		{
			Point position(i * Window::getWidth() / 4, j * Window::getHeight() / 4);
			pos->setValue(i, j, position);

			num->setValue(i, j, 0);

			bricks->setValue(i, j, nullptr);
		}
			
	auto startText = gcnew Text(L"开始游戏");
	startButton = gcnew Button(startText);
	startButton->setAnchor(0.5, 0.5);
	startButton->setPos(Window::getWidth() / 2, Window::getHeight() / 2);
	this->addChild(startButton);

	auto replayText = gcnew Text(L"再来一局");
	replayButton = gcnew Button(replayText);
	replayButton->setAnchor(0.5, 0.5);
	replayButton->setPos(Window::getWidth() / 2, Window::getHeight() / 2);
	this->addChild(replayButton);
	replayButton->setVisible(false);

	auto func = std::bind(&MainScene::start, this);
	startButton->setClickFunc(func);
	replayButton->setClickFunc(func);
}

void MainScene::start()
{
	startButton->setVisible(false);
	replayButton->setVisible(false);

	clear();

	newBrick();

}

void MainScene::onUpdate()
{
	if (num && pos)
	{
		if (Input::isDown(KeyCode::Left))
		{
			pressLeft();
			if (isGameOver())
				end();
		}
		else if (Input::isDown(KeyCode::Right))
		{
			pressRight();
			if (isGameOver())
				end();
		}
		else if (Input::isDown(KeyCode::Up))
		{
			pressUp();
			if (isGameOver())
				end();
		}
		else if (Input::isDown(KeyCode::Down))
		{
			PressDown();
			if (isGameOver())
				end();
		}
	}
}

void MainScene::clear()
{
	this->removeAllChildren();
	
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			num->setValue(i, j, 0);
}

void MainScene::newBrick()
{
	std::vector<int> is, js;
	int number = 0;
	
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (num->getValue(i, j) == 0)
			{
				is.push_back(i);
				js.push_back(j);
				number++;
			}

	if (number == 0)
		return;

	int rand_num = rand() / number;
	bricks->getValue(is[rand_num], js[rand_num]) = gcnew Brick;
	(bricks->getValue(is[rand_num], js[rand_num]))->setPos(pos->getValue(is[rand_num], js[rand_num]));
	num->setValue(is[rand_num], js[rand_num], 2);
	this->addChild(bricks->getValue(is[rand_num], js[rand_num]));
}

void MainScene::end()
{
	replayButton->setVisible(true);
}

bool MainScene::isGameOver()
{
	int x[4] = { 0, 0, 1,-1},
		y[4] = { 1,-1, 0, 0};
	for(int i = 0; i < 4; i++)
		for (int j = 0; j < 4; ++j)
		{
			if (num->getValue(i, j) == 0)
				return false;
			if (num->getValue(i, j) == 2048)
				return true;
			for(int p = 0; p < 4; p++)
				for (int k = 0; k < 4; k++)
				{
					int xl = i + x[p], yl = j + y[k];
					if (xl >= 0 && xl < 4 && yl>0 && yl < 4 && (num->getValue(i, j) == num->getValue(xl, yl)))
						return false;
				}
		}
	return true;
}
