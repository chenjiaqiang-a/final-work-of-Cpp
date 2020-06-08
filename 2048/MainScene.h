#pragma once
/*
---*---��������(MainScene)---*---
�����: �¼�ǿ, ���
*/

#include <easy2d/easy2d.h>
#include <vector>
#include "brick.h"

using namespace easy2d;

class MainScene : public Scene
{
private:
	Sprite* bg = nullptr;                  //����
	int score;                             //��¼����
	int num[4][4];                         //4 X 4 �ľ�����Ϸ�����ֳ���
	Brick* bricks[4][4];                   //ȫ��16��ͼƬ
	Button* gameOverButton = nullptr;      //������Ϸ��ť
	Sprite* board = nullptr;               //��Ϸ������ĳɼ���ʾ���
	Text* scoreText = nullptr;             //�ɼ���������
	Text* scores = nullptr;                //����ɼ�
public:
	MainScene();           //���캯��
	void start();          //��ʼһ������Ϸ�ĳ�ʼ��
	void clear();          //����ϴ���Ϸ�ĺۼ�
	void newBrick();       //�ڿհ�λ���������һ��brick
	void onUpdate();       //�¼�ѭ��,�����������
	//-----��Ϸ�еĲ���-----
	void update_screen();  //ˢ����Ļ
	void move_to_left();   //�����ƶ�
	void move_to_right();  //�����ƶ�
	void move_to_up();     //�����ƶ�
	void move_to_down();   //�����ƶ�
	//----------------------
	bool isGameOver();     //�ж��Ƿ���Ϸ����
	void end();            //һ����Ϸ���������end
	void GameOver();       //������Ϸ���ز˵�
};

MainScene::MainScene()
{
	bg = gcnew Sprite(L"./image/playbg.png");                //���ر���ͼƬ
	bg->setPos(0, 0);
	this->addChild(bg);

	score = 0;                                               //��ʼ������Ϊ0�����־���Ϊ0���򳡾��е���16��ͼƬ������
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
	  
	board = gcnew Sprite(L"./image/board.png");             //���������ƣ����������ͽ�����Ϸ��ť
	board->setAnchor(0.5, 0.5);
	board->setPos(Window::getWidth() / 2, Window::getHeight() / 2);

	scoreText = gcnew Text(L"�÷�: ");                      //����������ӷ���
	scores = gcnew Text(L"0");
	scoreText->setAnchor(0.5, 0.5);
	scores->setAnchor(0.5, 0.5);
	scoreText->setPos(board->getWidth() * 0.4, board->getHeight() * 0.3);
	scores->setPos(board->getWidth() * 0.6, board->getHeight() * 0.3);
	board->addChild(scoreText);
	board->addChild(scores);

	auto overpic = gcnew Sprite(L"./image/endButton.png");   //����������ӽ�����ť
	gameOverButton = gcnew Button(overpic);
	gameOverButton->setAnchor(0.5, 0.5);
	gameOverButton->setPos(board->getWidth() / 2, board->getHeight() * 0.6);
	board->addChild(gameOverButton);

	auto func = std::bind(&MainScene::GameOver, this);       //���ð�ť�������
	gameOverButton->setClickFunc(func);

	this->addChild(board);                                   //���ؽ������
	board->setVisible(false);

	this->setAutoUpdate(false);                              //��ͣ�¼�ѭ��
}

void MainScene::start()
{//��ʼһ������Ϸ��Ϸ�����ؽ�����壬������, �����ʼ���������ַ���
	board->setVisible(false);
	gameOverButton->setVisible(false);

	clear();

	newBrick();
	newBrick();
	this->setAutoUpdate(true);              //�����¼�ѭ��
}

void MainScene::onUpdate()
{//�¼�ѭ�������������벢������Ӧ
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
{//�����Ϸ�ۼ������־������㣬���ַ���ȫ������
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			num[i][j] = 0;
			bricks[i][j]->setVisible(false);
		}
}

void MainScene::newBrick()
{//����ڿ�λ����һ��2/4�����ַ���
	std::vector<int> is, js;             //��¼��λ������
	int number = 0;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (num[i][j] == 0)
			{
				is.push_back(i);
				js.push_back(j);
				number++;
			}

	if (number == 0)                    //�޿�λ������������
		return;

	int rand_num = Random::range(0, number - 1);
	bricks[is[rand_num]][js[rand_num]]->set_num();

	num[is[rand_num]][js[rand_num]] = bricks[is[rand_num]][js[rand_num]]->get_num();
	bricks[is[rand_num]][js[rand_num]]->setVisible(true);
}

void MainScene::end()
{//���˻���Ӯ�ˣ�ֹͣ�¼�ѭ������ʾ������壬���������н�����Ϸ��ť
	this->setAutoUpdate(false);
	scores->setText(std::to_wstring(score));
	board->setVisible(true);
	gameOverButton->setVisible(true);
}

void MainScene::GameOver()
{//���������Ϸ��ť������GameOver������������Ϸ���������Ԫ�أ����ز˵�����
	board->setVisible(false);
	gameOverButton->setVisible(false);
	this->setVisible(false);
	SceneManager::back();
}

bool MainScene::isGameOver()
{//�ж��Ƿ���Ϸ����
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
{//ÿ�β���ʹ���־������ı�ʱ��ͬ���������ַ���
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
		int b[4] = { 0 };                                 //����һ����ʱ�������洢���֮������		
		k = 0;
		for (int j = 0; j < 3; j++)
		{
			if (num[j][i] != 0)
			{
				int flag = 0;
				for (int l = j + 1; l < 4; l++)
				{                                         //���Ƿ�����ͬ����				
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
			num[j][i] = b[j];                            //��������ǻ�ȥ		
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
	for (int i = 0; i < 4; i++)                          //��ÿһ�п�ʼ
	{
		int b[4] = { 0 };				                 //����һ����ʱ�������洢���֮������		
		k = 3;
		for (int j = 3; j > 0; j--)
		{
			if (num[j][i] != 0) {
				int flag = 0;
				for (int l = j - 1; l >= 0; l--)         //���Ƿ�����ͬ����	
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
		b[k] = num[0][i];                                 //���һ��û�м�飬��ֵ��ȥ�������Ƿ�Ϊ0��������ν��		
		for (int j = 0; j < 4; j++)                       //����Ƿ����ƶ�
		{
			if (num[j][i] != b[j]) {
				tag = 1;
				break;
			}
		}
		for (int j = 0; j < 4; j++)
			num[j][i] = b[j];
	}
	if (tag)                                              //�����ƶ��������µ���
	{
		update_screen();
		newBrick();
	}
}