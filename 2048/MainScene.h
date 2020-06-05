#pragma once
/*
---*---主场景类---*---
完成者: 陈家强, 张涔
*/

#include <easy2d/easy2d.h>
#include <vector>
#include <iostream>
#include "brick.h"

using namespace easy2d;

class MainScene : public Scene
{
private:
	int score;                             //记录分数
	int num[4][4];                         //4 X 4 的矩阵，游戏的数字抽象
	Brick* bricks[4][4];                   //全屏16个图片
	Button* startButton = nullptr;         //开始按钮
	Button* replayButton = nullptr;        //重玩按钮
public:
	MainScene();           //构造函数
	void start();          //点击"开始游戏"或"再来一局",执行strat进行场景初始化
	void clear();          //清楚上次游戏的痕迹
	void newBrick();       //在空白位子随机产生一个brick
	//-----游戏中的操作-----
	void update_screen();  //刷新屏幕
	void move_to_left();   //向左移动
	void move_to_right();  //向右移动
	void move_to_up();     //向上移动
	void move_to_down();   //向下移动
	//----------------------
	bool isGameOver();     //判断是否游戏结束
	void end();            //一场游戏结束后调用end
	void onUpdate();       //事件循环,处理玩家命令
};

MainScene::MainScene()
{
	score = 0;                                               //初始化分数为0，数字矩阵为0，向场景中导入16张图片并隐藏
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
		{
			num[i][j] = 0;
			bricks[i][j] = gcnew Brick;
			Point pos(j * Window::getWidth() / 4, i * Window::getHeight() / 4);
			bricks[i][j]->setPos(pos);
			this->addChild(bricks[i][j]);
			bricks[i][j]->setVisible(false);
		}

	std::cout << Window::getHeight() << " " << Window::getWidth() / 4 << "\n" << bricks[0][1]->getHeight() << " " << bricks[0][1]->getWidth() << " " << bricks[0][1]->getPosX()<<" "<< bricks[0][1]->getPosY();

	auto startText = gcnew Text(L"开始游戏");                //创建开始按钮和重玩按钮
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

	auto func = std::bind(&MainScene::start, this);         //设置按钮点击函数
	startButton->setClickFunc(func);
	replayButton->setClickFunc(func);

	this->setAutoUpdate(false);
}

void MainScene::start()
{
	startButton->setVisible(false);        //隐藏按钮,清空场景
	replayButton->setVisible(false);

	clear();

	newBrick();
	newBrick();
	this->setAutoUpdate(true);
}

void MainScene::onUpdate()
{
	if (Input::isDown(KeyCode::Left))
	{
		move_to_left();
		if (isGameOver())
			end();
		Sleep(200);
	}
	else if (Input::isDown(KeyCode::Right))
	{

		move_to_right();
		if (isGameOver())
			end();
		Sleep(200);
	}
	else if (Input::isDown(KeyCode::Up))
	{
		move_to_up();
		if (isGameOver())
			end();
		Sleep(200);
	}
	else if (Input::isDown(KeyCode::Down))
	{
		move_to_down();
		if (isGameOver())
			end();
		Sleep(200);
	}
}

void MainScene::clear()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			num[i][j] = 0;
			bricks[i][j]->setVisible(false);
		}
}

void MainScene::newBrick()
{
	std::vector<int> is, js;
	int number = 0;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (num[i][j] == 0)
			{
				is.push_back(i);
				js.push_back(j);
				number++;
			}

	if (number == 0)
		return;

	int rand_num = Random::range(0, number - 1);
	bricks[is[rand_num]][js[rand_num]]->set_num();

	num[is[rand_num]][js[rand_num]] = bricks[is[rand_num]][js[rand_num]]->get_num();
	bricks[is[rand_num]][js[rand_num]]->setVisible(true);
}

void MainScene::end()
{
	this->setAutoUpdate(false);
	replayButton->setVisible(true);
}

bool MainScene::isGameOver()
{
	int x[4] = { 0, 0, 1,-1 },
		y[4] = { 1,-1, 0, 0 };
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; ++j)
		{
			if (num[i][j] == 0)
				return false;
			if (num[i][j] == 2048)
				return true;
			for (int p = 0; p < 4; p++)
			{
				int xl = i + x[p], yl = j + y[p];
				if (xl >= 0 && xl < 4 && yl>0 && yl < 4 && (num[i][j] == num[xl][yl]))
					return false;
			}
		}
	return true;
}

void MainScene::update_screen()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (num[i][j] != 0)
			{
				bricks[i][j]->set_num(num[i][j]);
				bricks[i][j]->setVisible(true);
			}
			else
			{
				bricks[i][j]->setVisible(false);
			}
		}
}

void MainScene::move_to_left()
{
	int k, tag = 0;
	for (int i = 0; i < 4; i++)
	{
		int b[4] = { 0 };
		k = 0;
		for (int j = 0; j < 3; j++)
		{
			if (num[i][j] != 0)
			{
				int flag = 0;
				for (int l = j + 1; l < 4; l++)
				{
					if (num[i][l] != 0)
					{
						flag = 1;
						if (num[i][l] == num[i][j])
						{
							b[k++] = 2 * num[i][j];
							score++;
							num[i][j] = num[i][l] = 0;
							break;
						}
						else
						{
							b[k++] = num[i][j];
							break;
						}
					}
				}
				if (flag == 0)
					b[k++] = num[i][j];
			}
		}
		b[k] = num[i][3];
		for (int j = 0; j < 4; j++)
		{
			if (num[i][j] != b[j])
			{
				tag = 1;
				break;
			}
		}
		for (int j = 0; j < 4; j++)
			num[i][j] = b[j];
	}
	if (tag)
	{
		update_screen();
		newBrick();
	}
}

void MainScene::move_to_right()
{
	int k, tag = 0;
	for (int i = 0; i < 4; i++)
	{
		int b[4] = { 0 };
		k = 3;
		for (int j = 3; j > 0; j--)
		{
			if (num[i][j] != 0)
			{
				int flag = 0;
				for (int l = j - 1; l >= 0; l--)
				{
					if (num[i][l] != 0)
					{
						flag = 1;
						if (num[i][l] == num[i][j])
						{
							b[k--] = 2 * num[i][j];
							score++;
							num[i][j] = num[i][l] = 0;
							break;
						}
						else
						{
							b[k--] = num[i][j];
							break;
						}
					}
				}
				if (flag == 0)
					b[k--] = num[i][j];
			}
		}
		b[k] = num[i][0];
		for (int j = 0; j < 4; j++)
		{
			if (num[i][j] != b[j])
			{
				tag = 1;
				break;
			}
		}
		for (int j = 0; j < 4; j++)
			num[i][j] = b[j];
	}
	if (tag)
	{
		update_screen();
		newBrick();
	}
}

void MainScene::move_to_up()
{
	int k, tag = 0;
	for (int i = 0; i < 4; i++)
	{
		int b[4] = { 0 };                 //定义一个临时数组来存储相加之后的情况		
		k = 0;
		for (int j = 0; j < 3; j++)
		{
			if (num[j][i] != 0)
			{
				int flag = 0;
				for (int l = j + 1; l < 4; l++)
				{    //找是否有相同的数				
					if (num[l][i] != 0)
					{
						flag = 1;
						if (num[l][i] == num[j][i])
						{
							b[k++] = 2 * num[j][i];
							score++;
							num[l][i] = num[j][i] = 0;
							break;
						}
						else
						{
							b[k++] = num[j][i];
							break;
						}
					}
				}
				if (flag == 0)
					b[k++] = num[j][i];
			}
		}
		b[k] = num[3][i];
		for (int j = 0; j < 4; j++)
		{
			if (num[j][i] != b[j])
			{
				tag = 1;
				break;
			}
		}
		for (int j = 0; j < 4; j++)
			num[j][i] = b[j];      //将结果覆盖回去		
	}
	if (tag)
	{
		update_screen();
		newBrick();
	}
}

void MainScene::move_to_down()
{
	int k, tag = 0;
	for (int i = 0; i < 4; i++)  //从每一列开始
	{
		int b[4] = { 0 };				 //定义一个临时数组来存储相加之后的情况		
		k = 3;
		for (int j = 3; j > 0; j--)
		{
			if (num[j][i] != 0) {
				int flag = 0;
				for (int l = j - 1; l >= 0; l--) //找是否有相同的数	
				{
					if (num[l][i] != 0)
					{
						flag = 1;
						if (num[l][i] == num[j][i])
						{
							b[k--] = 2 * num[j][i];
							score++;
							num[l][i] = num[j][i] = 0;
							break;
						}
						else
						{
							b[k--] = num[j][i];
							break;
						}
					}
				}
				if (flag == 0)b[k--] = num[j][i];
			}
		}
		b[k] = num[0][i];                 //最后一个没有检查，赋值过去，不管是否为0，都无所谓的		
		for (int j = 0; j < 4; j++) //检查是否有移动
		{
			if (num[j][i] != b[j]) {
				tag = 1;
				break;
			}
		}
		for (int j = 0; j < 4; j++)
			num[j][i] = b[j];
	}
	if (tag)                        //存在移动，产生新的数
	{
		update_screen();
		newBrick();
	}
}