//---------------------------------------------------------
// �������ƣ�������
// ���ߣ�Nomango
// ���뻷����Visual Studio 2017 / Easy2D v2.0.4
// ��Ŀ���ͣ�Win32 Application
//---------------------------------------------------------

#include <easy2d/easy2d.h>
#include "resource.h"
#include "StartScene.h"
#include "Data.h"

using namespace easy2d;

void Init();

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// ��ʼ����Ϸ
	if (Game::init(L"������", 640, 480))
	{
		// ���ô���ͼ��
		Window::setIcon(IDI_ICON1);

		// ��ʼ����Դ�ļ�
		Init();

		// ���뿪ʼ����
		auto scene = gcnew StartScene();
		SceneManager::enter(scene);

		// ��ʼ��Ϸ
		Game::start();
	}

	// ������Ϸ��Դ
	Game::destroy();
	return 0;
}

void Init()
{
	// Ԥ���������ļ�
	MusicPlayer::preload(L"res/background.wav");
	MusicPlayer::preload(L"res/boxmove.wav");
	MusicPlayer::preload(L"res/manmove.wav");
	// ѭ�����ű������֣�-1 ��ʾѭ������
	MusicPlayer::play(L"res/background.wav", -1);
	// ���ļ���ȡ�ؿ���Ϣ��δ��ȡ��ʱĬ��Ϊ 1
	g_CurrentLevel = Data::getInt(L"level", 1);
	// ���ļ���ȡ����������Ϣ��δ��ȡ��ʱĬ��Ϊ 1
	g_SoundOpen = Data::getBool(L"sound", true);
	if (!g_SoundOpen)
	{
		MusicPlayer::pause(L"res/background.wav");
	}
}
