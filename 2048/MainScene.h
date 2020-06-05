#pragma once
/*
---*---��������---*---
�����: �¼�ǿ, ���
*/

#include <easy2d/easy2d.h>
#include <vector>
#include <iostream>
#include "brick.h"

using namespace easy2d;

class MainScene : public Scene
{
private:
	int score;                             //��¼����
	int num[4][4];                         //4 X 4 �ľ�����Ϸ�����ֳ���
	Brick* bricks[4][4];                   //ȫ��16��ͼƬ
	Button* startButton = nullptr;         //��ʼ��ť
	Button* replayButton = nullptr;        //���水ť
public:
	MainScene();           //���캯��
	void start();          //���"��ʼ��Ϸ"��"����һ��",ִ��strat���г�����ʼ��
	void clear();          //����ϴ���Ϸ�ĺۼ�
	void newBrick();       //�ڿհ�λ���������һ��brick
	//-----��Ϸ�еĲ���-----
	void update_screen();  //ˢ����Ļ
	void move_to_left();   //�����ƶ�
	void move_to_right();  //�����ƶ�
	void move_to_up();     //�����ƶ�
	void move_to_down();   //�����ƶ�
	//----------------------
	bool isGameOver();     //�ж��Ƿ���Ϸ����
	void end();            //һ����Ϸ���������end
	void onUpdate();       //�¼�ѭ��,�����������
};

MainScene::MainScene()
{
	score = 0;                                               //��ʼ������Ϊ0�����־���Ϊ0���򳡾��е���16��ͼƬ������
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

	auto startText = gcnew Text(L"��ʼ��Ϸ");                //������ʼ��ť�����水ť
	startButton = gcnew Button(startText);
	startButton->setAnchor(0.5, 0.5);
	startButton->setPos(Window::getWidth() / 2, Window::getHeight() / 2);
	this->addChild(startButton);

	auto replayText = gcnew Text(L"����һ��");
	replayButton = gcnew Button(replayText);
	replayButton->setAnchor(0.5, 0.5);
	replayButton->setPos(Window::getWidth() / 2, Window::getHeight() / 2);
	this->addChild(replayButton);
	replayButton->setVisible(false);

	auto func = std::bind(&MainScene::start, this);         //���ð�ť�������
	startButton->setClickFunc(func);
	replayButton->setClickFunc(func);

	this->setAutoUpdate(false);
}

void MainScene::start()
{
	startButton->setVisible(false);        //���ذ�ť,��ճ���
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
		int b[4] = { 0 };                 //����һ����ʱ�������洢���֮������		
		k = 0;
		for (int j = 0; j < 3; j++)
		{
			if (num[j][i] != 0)
			{
				int flag = 0;
				for (int l = j + 1; l < 4; l++)
				{    //���Ƿ�����ͬ����				
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
			num[j][i] = b[j];      //��������ǻ�ȥ		
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
	for (int i = 0; i < 4; i++)  //��ÿһ�п�ʼ
	{
		int b[4] = { 0 };				 //����һ����ʱ�������洢���֮������		
		k = 3;
		for (int j = 3; j > 0; j--)
		{
			if (num[j][i] != 0) {
				int flag = 0;
				for (int l = j - 1; l >= 0; l--) //���Ƿ�����ͬ����	
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
		b[k] = num[0][i];                 //���һ��û�м�飬��ֵ��ȥ�������Ƿ�Ϊ0��������ν��		
		for (int j = 0; j < 4; j++) //����Ƿ����ƶ�
		{
			if (num[j][i] != b[j]) {
				tag = 1;
				break;
			}
		}
		for (int j = 0; j < 4; j++)
			num[j][i] = b[j];
	}
	if (tag)                        //�����ƶ��������µ���
	{
		update_screen();
		newBrick();
	}
}