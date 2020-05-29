#pragma once
#include <easy2d/easy2d.h>
#include "2Dmatrix.h"

using namespace easy2d;

class MainScene : public Scene
{
private:
	Matrix<Point>* pos;
	Button* startButton = nullptr;

public:
	MainScene();
	void start();
	void end();
	void onUpdate();
};

MainScene::MainScene()
{
	pos = gcnew Matrix<Point>(4, 4);
	for(int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
		{
			Point position(i * Window::getWidth() / 4, j * Window::getHeight() / 4);
			pos->setValue(i, j, position);
		}
			
}


