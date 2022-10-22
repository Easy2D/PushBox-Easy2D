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

	// 创建开始游戏按钮
	auto startBtn = gcnew MyTextButton(L"新游戏", [=]() {
		this->Start();
		});
	// 设置按钮位置
	startBtn->setPos(Window::getWidth() / 2, 260);
	this->addChild(startBtn);

	// 继续游戏按钮
	resumeBtn = gcnew MyTextButton(L"继续关卡", [=]() {
		this->Continue();
		});
	// 设置按钮位置
	resumeBtn->setPos(Window::getWidth() / 2, 300);
	// 若当前关卡是第一关，禁用这个按钮
	if (g_CurrentLevel == 1)
	{
		resumeBtn->setEnable(false);
	}
	this->addChild(resumeBtn);

	// 创建退出按钮
	auto exitBtn = gcnew MyTextButton(L"退出", [=]() {
		this->Exit();
		});
	// 设置按钮位置
	exitBtn->setPos(Window::getWidth() / 2, 340);
	this->addChild(exitBtn);

	// 创建声音开关按钮
	soundBtn = gcnew SoundButton();
	// 设置按钮位置
	soundBtn->setPos(50, 50);
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
	// 更新音乐按钮状态
	soundBtn->updateStatus();
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
