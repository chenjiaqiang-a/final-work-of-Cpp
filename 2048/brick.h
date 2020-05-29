#pragma once
#include <easy2d/easy2d.h>

using namespace easy2d;

class Brick : public Sprite
{
private:
	int num;
	Text* numText = nullptr;
public:
	Brick();
};

Brick::Brick()
{
	this->open(L"./image/pic.png");
	this->setAnchor(0.f, 0.f);
}

