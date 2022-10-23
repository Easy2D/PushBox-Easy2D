//---------------------------------------------------------
// 程序名称：推箱子
// 作者：Nomango
// 编译环境：Visual Studio 2017 / Easy2D v2.1.12
// 项目类型：Win32 Application
//---------------------------------------------------------

#include <easy2d/easy2d.h>
#include "resource.h"
#include "StartScene.h"
#include "Data.h"

using namespace easy2d;

void Init();

int APIENTRY wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ PWSTR, _In_ int)
{
	// 初始化游戏
	if (Game::init("推箱子", 640, 480))
	{
		// 设置窗口图标
		Window::setIcon(IDI_ICON1);

		// 初始化资源文件
		Init();

		// 进入开始场景
		auto scene = gcnew StartScene;
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
	MusicPlayer::preload("res/background.wav");
	MusicPlayer::preload("res/boxmove.wav");
	MusicPlayer::preload("res/manmove.wav");
	// 循环播放背景音乐，-1 表示循环播放
	MusicPlayer::play("res/background.wav", -1);
	// 从文件读取关卡信息，未读取到时默认为 1
	g_CurrentLevel = Data::getInt("level", 1);
	// 从文件读取声音开关信息，未读取到时默认为 1
	g_SoundOpen = Data::getBool("sound", true);
	if (!g_SoundOpen)
	{
		MusicPlayer::pause("res/background.wav");
	}
}
