//---------------------------------------------------------
// �������ƣ�������
// ���ߣ�Nomango
// ���뻷����Visual Studio 2017 / Easy2D v2.1.12
// ��Ŀ���ͣ�Win32 Application
//---------------------------------------------------------

#include <easy2d/easy2d.h>
#include "resource.h"
#include "StartScene.h"
#include "Data.h"

using namespace easy2d;

void Init();

int APIENTRY wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ PWSTR, _In_ int)
{
	// ��ʼ����Ϸ
	if (Game::init("������", 640, 480))
	{
		// ���ô���ͼ��
		Window::setIcon(IDI_ICON1);

		// ��ʼ����Դ�ļ�
		Init();

		// ���뿪ʼ����
		auto scene = gcnew StartScene;
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
	MusicPlayer::preload("res/background.wav");
	MusicPlayer::preload("res/boxmove.wav");
	MusicPlayer::preload("res/manmove.wav");
	// ѭ�����ű������֣�-1 ��ʾѭ������
	MusicPlayer::play("res/background.wav", -1);
	// ���ļ���ȡ�ؿ���Ϣ��δ��ȡ��ʱĬ��Ϊ 1
	g_CurrentLevel = Data::getInt("level", 1);
	// ���ļ���ȡ����������Ϣ��δ��ȡ��ʱĬ��Ϊ 1
	g_SoundOpen = Data::getBool("sound", true);
	if (!g_SoundOpen)
	{
		MusicPlayer::pause("res/background.wav");
	}
}
