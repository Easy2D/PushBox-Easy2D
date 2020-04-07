//---------------------------------------------------------
// 程序名称：推箱子
// 作者：Nomango
// 编译环境：Visual Studio 2017 / Easy2D v2.0.4
// 项目类型：Win32 Application
//---------------------------------------------------------

#include <easy2d/easy2d.h>
#include "resource.h"
#include "StartScene.h"
#include "Data.h"

using namespace easy2d;

void Init();

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// 初始化游戏
	if (Game::init(L"推箱子", 640, 480))
	{
		// 设置窗口图标
		Window::setIcon(IDI_ICON1);

		// 初始化资源文件
		Init();

		// 进入开始场景
		auto scene = gcnew StartScene();
		SceneManager::enter(scene);

		// 开始游戏
		Game::start();
	}

	// 回收游戏资源
	Game::destroy();
	return 0;
}

void Init()
{
	// 预加载音乐文件
	MusicPlayer::preload(L"res/background.wav");
	MusicPlayer::preload(L"res/boxmove.wav");
	MusicPlayer::preload(L"res/manmove.wav");
	// 循环播放背景音乐，-1 表示循环播放
	MusicPlayer::play(L"res/background.wav", -1);
	// 从文件读取关卡信息，未读取到时默认为 1
	g_CurrentLevel = Data::getInt(L"level", 1);
	// 从文件读取声音开关信息，未读取到时默认为 1
	g_SoundOpen = Data::getBool(L"sound", true);
	if (!g_SoundOpen)
	{
		MusicPlayer::pause(L"res/background.wav");
	}
}
