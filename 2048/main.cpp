#include <easy2d/easy2d.h>


using namespace easy2d;

constexpr auto WIDTH = 120;
constexpr auto HEIGHT = 120;

using namespace easy2d;

int main()
{
    if (Game::init())                               // 初始化游戏
    {
        Window::setTitle(L"2048");
        Window::setSize(WIDTH, HEIGHT);
        Logger::showConsole(false);

        auto scene = gcnew Scene;
        SceneManager::enter(scene);

        //auto scene = gcnew MainScene;                   // 创建一个场景
        //SceneManager::enter(scene);                 // 进入该场景

        Game::start();                              // 开始游戏
    }
    Game::destroy();
    return 0;
}
