#include <easy2d/easy2d.h>
#include "brick.h"

using namespace easy2d;

constexpr auto WIDTH = 120;
constexpr auto HEIGHT = 120;

int main()
{
    if (Game::init())                               // 初始化游戏
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

        //auto scene = gcnew MainScene;                   // 创建一个场景
        //SceneManager::enter(scene);                 // 进入该场景

        Game::start();                              // 开始游戏
    }
    Game::destroy();
    return 0;
}
