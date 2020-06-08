/*
项目名称: 2048游戏
组员: 陈家强,尹子鳗,李妍,张涔
工具: VS 2019, Easy2D, PS
分工: 陈家强->MainScene类框架, 张涔->MainScene类操作函数, 尹子鳗->Menu类, 李妍->Brick类
(报告/尹子鳗, 游戏图片/陈家强)
*/

#include <easy2d/easy2d.h>
#include "Menu.h"

using namespace easy2d;

constexpr auto WIDTH = 600;
constexpr auto HEIGHT = 600;

int main()
{
    if (Game::init())                                    // 初始化游戏
    {
        Window::setTitle(L"2048");
        Window::setSize(WIDTH, HEIGHT);
        Logger::showConsole(false);

        auto scene = gcnew MenuScene;                   // 创建一个场景
        SceneManager::enter(scene);                     // 进入该场景

        Game::start();                                  // 开始游戏
    }
    Game::destroy();
    return 0;
}