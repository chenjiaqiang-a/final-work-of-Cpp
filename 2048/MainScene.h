#pragma once
/*
---*---主场景类(MainScene)---*---
完成者: 陈家强, 张涔
*/

#include <easy2d/easy2d.h>
#include <vector>
#include "brick.h"

using namespace easy2d;

class MainScene : public Scene
{
private:
	Sprite* bg = nullptr;                  //背景
	int score;                             //记录分数
	int num[4][4];                         //4 X 4 的矩阵，游戏的数字抽象
	Brick* bricks[4][4];                   //全屏16个图片
	Button* gameOverButton = nullptr;      //结束游戏按钮
	Sprite* board = nullptr;               //游戏结束后的成绩显示面板
	Text* scoreText = nullptr;             //成绩叙述文字
	Text* scores = nullptr;                //具体成绩
public:
	MainScene();           //构造函数
	void start();          //开始一轮新游戏的初始化
	void clear();          //清楚上次游戏的痕迹
	void newBrick();       //在空白位子随机产生一个brick
	void onUpdate();       //事件循环,处理玩家命令
	//-----游戏中的操作-----
	void update_screen();  //刷新屏幕
	void move_to_left();   //向左移动
	void move_to_right();  //向右移动
	void move_to_up();     //向上移动
	void move_to_down();   //向下移动
	//----------------------
	bool isGameOver();     //判断是否游戏结束
	void end();            //一场游戏结束后调用end
	void GameOver();       //结束游戏返回菜单
};

MainScene::MainScene()
{
	bg = gcnew Sprite(L"./image/playbg.png");                //加载背景图片
	bg->setPos(0, 0);
	this->addChild(bg);

	score = 0;                                               //初始化分数为0，数字矩阵为0，向场景中导入16张图片并隐藏
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
		{
			num[i][j] = 0;
			bricks[i][j] = gcnew Brick;
			Point pos(j * Window::getHeight() / 4, i * Window::getWidth() / 4);
			bricks[i][j]->setPos(pos);
			this->addChild(bricks[i][j]);
			bricks[i][j]->setVisible(false);
		}
	  
	board = gcnew Sprite(L"./image/board.png");             //结束面板设计，包括分数和结束游戏按钮
	board->setAnchor(0.5, 0.5);
	board->setPos(Window::getWidth() / 2, Window::getHeight() / 2);

	scoreText = gcnew Text(L"得分: ");                      //向结束面板添加分数
	scores = gcnew Text(L"0");
	scoreText->setAnchor(0.5, 0.5);
	scores->setAnchor(0.5, 0.5);
	scoreText->setPos(board->getWidth() * 0.4, board->getHeight() * 0.3);
	scores->setPos(board->getWidth() * 0.6, board->getHeight() * 0.3);
	board->addChild(scoreText);
	board->addChild(scores);

	auto overpic = gcnew Sprite(L"./image/endButton.png");   //向结束面板添加结束按钮
	gameOverButton = gcnew Button(overpic);
	gameOverButton->setAnchor(0.5, 0.5);
	gameOverButton->setPos(board->getWidth() / 2, board->getHeight() * 0.6);
	board->addChild(gameOverButton);

	auto func = std::bind(&MainScene::GameOver, this);       //设置按钮点击函数
	gameOverButton->setClickFunc(func);

	this->addChild(board);                                   //隐藏结束面板
	board->setVisible(false);

	this->setAutoUpdate(false);                              //暂停事件循环
}

void MainScene::start()
{//开始一轮新游戏游戏，隐藏结束面板，清理场景, 随机初始化两个数字方块
	board->setVisible(false);
	gameOverButton->setVisible(false);

	clear();

	newBrick();
	newBrick();
	this->setAutoUpdate(true);              //启动事件循环
}

void MainScene::onUpdate()
{//事件循环，检测玩家输入并做出反应
	if (Input::isDown(KeyCode::Left))
	{
		move_to_left();
		if (isGameOver())
			end();
		Sleep(250);
	}
	else if (Input::isDown(KeyCode::Right))
	{

		move_to_right();
		if (isGameOver())
			end();
		Sleep(250);
	}
	else if (Input::isDown(KeyCode::Up))
	{
		move_to_up();
		if (isGameOver())
			end();
		Sleep(250);
	}
	else if (Input::isDown(KeyCode::Down))
	{
		move_to_down();
		if (isGameOver())
			end();
		Sleep(250);
	}
}

void MainScene::clear()
{//清空游戏痕迹，数字矩阵置零，数字方块全部隐藏
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			num[i][j] = 0;
			bricks[i][j]->setVisible(false);
		}
}

void MainScene::newBrick()
{//随机在空位产生一块2/4的数字方块
	std::vector<int> is, js;             //记录空位的坐标
	int number = 0;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (num[i][j] == 0)
			{
				is.push_back(i);
				js.push_back(j);
				number++;
			}

	if (number == 0)                    //无空位，不产生方块
		return;

	int rand_num = Random::range(0, number - 1);
	bricks[is[rand_num]][js[rand_num]]->set_num();

	num[is[rand_num]][js[rand_num]] = bricks[is[rand_num]][js[rand_num]]->get_num();
	bricks[is[rand_num]][js[rand_num]]->setVisible(true);
}

void MainScene::end()
{//输了或者赢了，停止事件循环，显示结束面板，分数，还有结束游戏按钮
	this->setAutoUpdate(false);
	scores->setText(std::to_wstring(score));
	board->setVisible(true);
	gameOverButton->setVisible(true);
}

void MainScene::GameOver()
{//点击结束游戏按钮，调用GameOver函数，隐藏游戏场景及相关元素，返回菜单场景
	board->setVisible(false);
	gameOverButton->setVisible(false);
	this->setVisible(false);
	SceneManager::back();
}

bool MainScene::isGameOver()
{//判断是否游戏结束
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
				if (xl >= 0 && xl < 4 && yl>=0 && yl < 4 && (num[i][j] == num[xl][yl]))
					return false;
			}
		}
	return true;
}

void MainScene::update_screen()
{//每次操作使数字矩阵发生改变时，同步更新数字方块
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
		int b[4] = { 0 };                                 //定义一个临时数组来存储相加之后的情况		
		k = 0;
		for (int j = 0; j < 3; j++)
		{
			if (num[j][i] != 0)
			{
				int flag = 0;
				for (int l = j + 1; l < 4; l++)
				{                                         //找是否有相同的数				
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
			num[j][i] = b[j];                            //将结果覆盖回去		
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
	for (int i = 0; i < 4; i++)                          //从每一列开始
	{
		int b[4] = { 0 };				                 //定义一个临时数组来存储相加之后的情况		
		k = 3;
		for (int j = 3; j > 0; j--)
		{
			if (num[j][i] != 0) {
				int flag = 0;
				for (int l = j - 1; l >= 0; l--)         //找是否有相同的数	
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
		b[k] = num[0][i];                                 //最后一个没有检查，赋值过去，不管是否为0，都无所谓的		
		for (int j = 0; j < 4; j++)                       //检查是否有移动
		{
			if (num[j][i] != b[j]) {
				tag = 1;
				break;
			}
		}
		for (int j = 0; j < 4; j++)
			num[j][i] = b[j];
	}
	if (tag)                                              //存在移动，产生新的数
	{
		update_screen();
		newBrick();
	}
}