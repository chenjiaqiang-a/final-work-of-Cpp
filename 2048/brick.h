#pragma once
#include <easy2d/easy2d.h>
#include <string>
#include <random>

using namespace easy2d;

class Brick : public Sprite
{
private:
	int num;
	Text* numText = nullptr;
public:
	Brick();
	Brick(int);
	void load_pic();
	int get_num();
	void set_num(int);
	void set_num();
};



Brick::Brick(int n)
{
	num = n;
	load_pic();
}

void Brick::load_pic()
{
	switch (num)
	{
	case 2: this->open(L"./image/pic_2.png"); break;
	case 4: this->open(L"./image/pic_4.png"); break;
	case 8: this->open(L"./image/pic_8.png"); break;
	case 16: this->open(L"./image/pic_16.png"); break;
	case 32: this->open(L"./image/pic_32.png"); break;
	case 64: this->open(L"./image/pic_64.png"); break;
	case 128: this->open(L"./image/pic_128.png"); break;
	case 256: this->open(L"./image/pic_256.png"); break;
	case 512: this->open(L"./image/pic_512.png"); break;
	case 1024: this->open(L"./image/pic_1024.png"); break;
	case 2048: this->open(L"./image/pic_2048.png"); break;
	}
	this->setAnchor(0.f, 0.f);
}

Brick::Brick()
{
	int rand_num = Random::range(1, 4);
	if (rand_num == 4)
		num = 4;
	else
		num = 2;
	load_pic();
}

int Brick::get_num()
{
	return num;
}

void Brick::set_num(int n)
{
	num = n;
	load_pic();
}

void Brick::set_num()
{
	int rand_num = Random::range(1, 4);
	if (rand_num == 4)
		num = 4;
	else
		num = 2;
	load_pic();
}
