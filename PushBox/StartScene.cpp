#include "StartScene.h"
#include "PlayScene.h"
#include "Data.h"

StartScene::StartScene()
{
	// 添加背景图
	auto background = gcnew Sprite(L"res/start.jpg");
	this->addChild(background);

	// 修改节点默认中心点位置
	Node::setDefaultAnchor(0.5, 0.5);

	// 创建字体
	auto fontNormal = Font(L"新宋体", 28, Font::Weight::Bold);
	auto fontSelect = Font(L"新宋体", 28, Font::Weight::Bold);
	auto fontDisable = Font(L"新宋体", 28, Font::Weight::Bold);

	// 创建样式
	auto styleNormal = Text::Style(Color::Black);
	auto styleSelect = Text::Style(Color::Blue);
	auto styleDisable = Text::Style(Color::LightGray);

	// 创建开始游戏按钮
	auto startBtn = gcnew Button();
	startBtn->setNormal(gcnew Text(L"新游戏", fontNormal, styleNormal));
	startBtn->setMouseOver(gcnew Text(L"新游戏", fontSelect, styleSelect));
	// 设置按钮位置
	startBtn->setPos(Window::getWidth() / 2, 260);
	// 设置按钮回调函数
	startBtn->setClickFunc(std::bind(&StartScene::Start, this));
	this->addChild(startBtn);

	// 继续游戏按钮
	resumeBtn = gcnew Button();
	resumeBtn->setNormal(gcnew Text(L"继续关卡", fontNormal, styleNormal));
	resumeBtn->setMouseOver(gcnew Text(L"继续关卡", fontSelect, styleSelect));
	resumeBtn->setDisabled(gcnew Text(L"继续关卡", fontDisable, styleDisable));
	// 设置按钮位置
	resumeBtn->setPos(Window::getWidth() / 2, 300);
	// 若当前关卡是第一关，禁用这个按钮
	if (g_CurrentLevel == 1)
	{
		resumeBtn->setEnable(false);
	}
	// 设置按钮回调函数
	resumeBtn->setClickFunc(std::bind(&StartScene::Continue, this));
	this->addChild(resumeBtn);

	// 创建退出按钮
	auto exitBtn = gcnew Button();
	exitBtn->setNormal(gcnew Text(L"退出", fontNormal, styleNormal));
	exitBtn->setMouseOver(gcnew Text(L"退出", fontSelect, styleSelect));
	// 设置按钮位置
	exitBtn->setPos(Window::getWidth() / 2, 340);
	// 设置按钮回调函数
	exitBtn->setClickFunc(std::bind(&StartScene::Exit, this));
	this->addChild(exitBtn);

	// 创建声音开关按钮
	soundBtn = gcnew Button(gcnew Sprite(g_SoundOpen ? L"res/soundon.png" : L"res/soundoff.png"));
	// 设置按钮位置
	soundBtn->setPos(50, 50);
	// 设置按钮回调函数
	soundBtn->setClickFunc(std::bind(&StartScene::Sound, this));
	this->addChild(soundBtn);

	// 恢复节点默认中心点位置
	Node::setDefaultAnchor(0, 0);
}

void StartScene::onEnter()
{
	// 当前关卡不为 1 时，可以继续游戏
	if (g_CurrentLevel == 1)
	{
		resumeBtn->setEnable(false);
	}
	else
	{
		resumeBtn->setEnable(true);
	}
}

void StartScene::Start()
{
	// 创建 PlayScene 场景
	auto scene = gcnew PlayScene(1);
	// 切换到 PlayScene 场景
	SceneManager::enter(scene);
}

void StartScene::Continue()
{
	// 创建 PlayScene 场景
	auto scene = gcnew PlayScene(g_CurrentLevel);
	// 切换到 PlayScene 场景
	SceneManager::enter(scene);
}

void StartScene::Exit()
{
	// 退出游戏
	Game::quit();
}

void StartScene::Sound()
{
	// 获取按钮状态
	if (!g_SoundOpen)
	{
		// 继续背景音乐
		MusicPlayer::resume(L"res/background.wav");
		soundBtn->setNormal(gcnew Sprite(L"res/soundon.png"));
		g_SoundOpen = true;
	}
	else
	{
		// 暂停背景音乐
		MusicPlayer::pause(L"res/background.wav");
		soundBtn->setNormal(gcnew Sprite(L"res/soundoff.png"));
		g_SoundOpen = false;
	}
	// 保存信息到文件
	Data::saveBool(L"sound", g_SoundOpen);
}
