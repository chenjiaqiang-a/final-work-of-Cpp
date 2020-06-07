#pragma once
/*
---*---数字方块类(Brick)---*---
完成者: 李妍
*/


#include <easy2d/easy2d.h>
using namespace easy2d;
class Brick :public Sprite
{
private:
	int num;
public:
	Brick();
	Brick(int);
	void loadpic();
	void set_num();
	void set_num(int);
	int get_num();

};

//对应数字的位置加载对应的图片
void Brick::loadpic() {
	switch (num) {
	case 2:this->open(L"./image/pic_2.png"); break;
	case 4:this->open(L"./image/pic_4.png"); break;
	case 8:this->open(L"./image/pic_8.png"); break;
	case 16:this->open(L"./image/pic_16.png"); break;
	case 32:this->open(L"./image/pic_32.png"); break;
	case 64:this->open(L"./image/pic_64.png"); break;
	case 128:this->open(L"./image/pic_128.png"); break;
	case 256:this->open(L"./image/pic_256.png"); break;
	case 512:this->open(L"./image/pic_512.png"); break;
	case 1024:this->open(L"./image/pic_1024.png"); break;
	case 2048:this->open(L"./image/pic_2048.png"); break;
	}
	this->setAnchor(0, 0);
}

//开始游戏时随机产生2/4，并使产生2的概率是3/4，产生4的概率是1/4
Brick::Brick() {
	int ran_num = Random::range(1, 4);
	if (ran_num == 4)
	{
		num = 4;
	}
	else
	{
		num = 2;
	}
	loadpic();
}

//测试时保证每张图片可用
Brick::Brick(int n) {
	num = n;
	loadpic();
}

//返回图片所代表的数字（用于计算）
int Brick::get_num() {
	return num;
}

//每次操作时随机产生新的2/4
void Brick::set_num() {
	int ran_num = Random::range(1, 4);
	if (ran_num == 4)
	{
		num = 4;
	}
	else
	{
		num = 2;
	}
	loadpic();
}

//在数字改变时调用
void Brick::set_num(int n) {
	num = n;
	loadpic();
}