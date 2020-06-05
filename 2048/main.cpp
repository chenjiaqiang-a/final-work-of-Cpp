#include <easy2d/easy2d.h>
#include "MainScene.h"

using namespace easy2d;

constexpr auto WIDTH = 600;
constexpr auto HEIGHT = 600;

int main()
{
    if (Game::init())                               // ��ʼ����Ϸ
    {
        Window::setTitle(L"2048");
        Window::setSize(WIDTH, HEIGHT);
        Logger::showConsole(true);

        auto scene = gcnew MainScene;               // ����һ������
        SceneManager::enter(scene);                 // ����ó���

        Game::start();                              // ��ʼ��Ϸ
    }
    Game::destroy();
    return 0;
}
