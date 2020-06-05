#include <easy2d/easy2d.h>
#include "MainScene.h"

using namespace easy2d;

constexpr auto WIDTH = 600;
constexpr auto HEIGHT = 600;

int main()
{
    if (Game::init())                               // 初始化游戏
    {
        Window::setTitle(L"2048");
        Window::setSize(WIDTH, HEIGHT);
        Logger::showConsole(true);

        auto scene = gcnew MainScene;               // 创建一个场景
        SceneManager::enter(scene);                 // 进入该场景

        Game::start();                              // 开始游戏
    }
    Game::destroy();
    return 0;
}
