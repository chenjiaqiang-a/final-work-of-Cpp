/*
��Ŀ����: 2048��Ϸ
��Ա: �¼�ǿ,������,����,���
����: VS 2019, Easy2D, PS
�ֹ�: �¼�ǿ->MainScene����, ���->MainScene���������, ������->Menu��, ����->Brick��
(����/������, ��ϷͼƬ/�¼�ǿ)
*/

#include <easy2d/easy2d.h>
#include "Menu.h"

using namespace easy2d;

constexpr auto WIDTH = 600;
constexpr auto HEIGHT = 600;

int main()
{
    if (Game::init())                                    // ��ʼ����Ϸ
    {
        Window::setTitle(L"2048");
        Window::setSize(WIDTH, HEIGHT);
        Logger::showConsole(false);

        auto scene = gcnew MenuScene;                   // ����һ������
        SceneManager::enter(scene);                     // ����ó���

        Game::start();                                  // ��ʼ��Ϸ
    }
    Game::destroy();
    return 0;
}