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
	void doubleNum();
};

Brick::Brick()
{
	this->open(L"./image/pic.png");
	this->setAnchor(0.f, 0.f);
	
	num = 2;
	numText = gcnew Text(std::to_wstring(num));
	numText->setAnchor(0.5, 0.5);
	numText->setPos(this->getWidth() / 2, this->getHeight() / 2);
	this->addChild(numText);
}

void Brick::doubleNum()
{
	num *= 2;
	numText->setText(std::to_wstring(num));
}

