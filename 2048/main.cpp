#include <easy2d/easy2d.h>


using namespace easy2d;

constexpr auto WIDTH = 120;
constexpr auto HEIGHT = 120;

using namespace easy2d;

int main()
{
    if (Game::init())                               // ��ʼ����Ϸ
    {
        Window::setTitle(L"2048");
        Window::setSize(WIDTH, HEIGHT);
        Logger::showConsole(false);

        auto scene = gcnew Scene;
        SceneManager::enter(scene);

        //auto scene = gcnew MainScene;                   // ����һ������
        //SceneManager::enter(scene);                 // ����ó���

        Game::start();                              // ��ʼ��Ϸ
    }
    Game::destroy();
    return 0;
}
