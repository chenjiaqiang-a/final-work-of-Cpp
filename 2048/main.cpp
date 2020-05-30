#include <easy2d/easy2d.h>
#include "brick.h"

using namespace easy2d;

constexpr auto WIDTH = 120;
constexpr auto HEIGHT = 120;

int main()
{
    if (Game::init())                               // ��ʼ����Ϸ
    {
        Window::setTitle(L"2048");
        Window::setSize(WIDTH, HEIGHT);
        Logger::showConsole(false);

        auto scene = gcnew Scene;
        SceneManager::enter(scene);

        auto brick1 = gcnew Brick;
        auto brick2 = gcnew Brick;

        brick1->setPos(0, 0);
        brick2->setPos(30, 30);
        brick2->doubleNum();

        scene->addChild(brick1);
        scene->addChild(brick2);

        //auto scene = gcnew MainScene;                   // ����һ������
        //SceneManager::enter(scene);                 // ����ó���

        Game::start();                              // ��ʼ��Ϸ
    }
    Game::destroy();
    return 0;
}
