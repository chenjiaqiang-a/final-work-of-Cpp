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
	void moveBrick(int, int, int, int);
	void move_to_left(int,int);
	void move_to_right(int, int);
	void move_to_up(int, int);
	void move_to_down(int, int);
	void pressLeft();
	void pressRight();
	void pressUp();
	void pressDown();
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
	this->addChild(pos);
	this->addChild(num);
	this->addChild(bricks);
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
			pressDown();
			if (isGameOver())
				end();
		}
	}
}

void MainScene::clear()
{	
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			num->setValue(i, j, 0);
			(bricks->getValue(i, j))->removeFromParent();
			delete bricks->getValue(i, j);
			bricks->setValue(i, j, nullptr);
		}
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


void MainScene::moveBrick(int prex, int prey, int x, int y)
{
	int temp_num = num->getValue(x, y);
	Brick* temp_brick = bricks->getValue(x, y);
	num->setValue(x, y, num->getValue(prex, prey));
	num->setValue(prex, prey, temp_num);
	bricks->setValue(x, y, bricks->getValue(prex, prey));
	bricks->setValue(prex, prey, temp_brick);
}

void MainScene::move_to_down(int i, int j)
{
	for (int p = j; p >= 0; p--)                     //将方块全部移向底部
		if (num->getValue(p, i) == 0)
		{
			int q = p - 1;
			while (q >= 0)
			{
				if (num->getValue(q, i) != 0)
					moveBrick(q, i, p, i);
				q--;
			}
		}
}

void MainScene::pressDown()
{
	for (int i = 0; i < 4; i++)
	{
		move_to_down(i, 3);

		int j = 3;
		while (j > 0)
		{
			if (num->getValue(j, i) != 0 && num->getValue(j, i) == num->getValue(j - 1, i))
			{//合并+移动
				num->getValue(j, i) *= 2;
				(bricks->getValue(j, i))->doubleNum();
				num->setValue(j - 1, i, 0);
				delete bricks->getValue(j - 1, i);
				bricks->setValue(j - 1, i, nullptr);
				
				move_to_down(i, j);
				j++;
			}
			else
				j--;
		}

		newBrick();
	}
}

void MainScene::move_to_up(int i, int j)
{
	for (int p = j; p < 4; p++)                     //将方块全部移向底部
		if (num->getValue(p, i) == 0)
		{
			int q = p + 1;
			while (q < 4)
			{
				if (num->getValue(q, i) != 0)
					moveBrick(q, i, p, i);
				q++;
			}
		}
}

void MainScene::pressUp()
{
	for (int i = 0; i < 4; i++)
	{
		move_to_up(i, 0);

		int j = 0;
		while (j < 3)
		{
			if (num->getValue(j, i) != 0 && num->getValue(j, i) == num->getValue(j + 1, i))
			{//合并+移动
				num->getValue(j, i) *= 2;
				(bricks->getValue(j, i))->doubleNum();
				num->setValue(j + 1, i, 0);
				delete bricks->getValue(j + 1, i);
				bricks->setValue(j + 1, i, nullptr);

				move_to_up(i, j);
				j++;
			}
			else
				j++;
		}

		newBrick();
	}
}

void MainScene::move_to_right(int i, int j)
{
	for (int p = j; p >= 0; p--)                     //将方块全部移向底部
		if (num->getValue(i, p) == 0)
		{
			int q = p - 1;
			while (q >= 0)
			{
				if (num->getValue(i, q) != 0)
					moveBrick(i, q, i, p);
				q--;
			}
		}
}

void MainScene::pressRight()
{
	for (int i = 0; i < 4; i++)
	{
		move_to_right(i, 3);

		int j = 3;
		while (j > 0)
		{
			if (num->getValue(i, j) != 0 && num->getValue(i, j) == num->getValue(i, j - 1))
			{//合并+移动
				num->getValue(i, j) *= 2;
				(bricks->getValue(i, j))->doubleNum();
				num->setValue(i, j - 1, 0);
				delete bricks->getValue(i, j - 1);
				bricks->setValue(i, j - 1, nullptr);

				move_to_right(i, j);
				j++;
			}
			else
				j--;
		}

		newBrick();
	}
}

void MainScene::move_to_left(int i, int j)
{
	for (int p = j; p < 4; p++)                     //将方块全部移向底部
		if (num->getValue(i, p) == 0)
		{
			int q = p + 1;
			while (q < 4)
			{
				if (num->getValue(i, q) != 0)
					moveBrick(i, q, i, p);
				q++;
			}
		}
}

void MainScene::pressLeft()
{
	for (int i = 0; i < 4; i++)
	{
		move_to_left(i, 0);

		int j = 0;
		while (j < 3)
		{
			if (num->getValue(i, j) != 0 && num->getValue(i, j) == num->getValue(i, j + 1))
			{//合并+移动
				num->getValue(i, j) *= 2;
				(bricks->getValue(i, j))->doubleNum();
				num->setValue(i, j + 1, 0);
				delete bricks->getValue(i, j + 1);
				bricks->setValue(i, j + 1, nullptr);

				move_to_left(i, j);
				j++;
			}
			else
				j++;
		}

		newBrick();
	}
}