#include "StartScene.h"
#include "PlayScene.h"
#include "Data.h"

StartScene::StartScene()
{
	// ��ӱ���ͼ
	auto background = gcnew Sprite(L"res/start.jpg");
	this->addChild(background);

	// �޸Ľڵ�Ĭ�����ĵ�λ��
	Node::setDefaultAnchor(0.5, 0.5);

	// ������ʼ��Ϸ��ť
	auto startBtn = gcnew MyTextButton(L"����Ϸ", [=]() {
		this->Start();
		});
	// ���ð�ťλ��
	startBtn->setPos(Window::getWidth() / 2, 260);
	this->addChild(startBtn);

	// ������Ϸ��ť
	resumeBtn = gcnew MyTextButton(L"�����ؿ�", [=]() {
		this->Continue();
		});
	// ���ð�ťλ��
	resumeBtn->setPos(Window::getWidth() / 2, 300);
	// ����ǰ�ؿ��ǵ�һ�أ����������ť
	if (g_CurrentLevel == 1)
	{
		resumeBtn->setEnable(false);
	}
	this->addChild(resumeBtn);

	// �����˳���ť
	auto exitBtn = gcnew MyTextButton(L"�˳�", [=]() {
		this->Exit();
		});
	// ���ð�ťλ��
	exitBtn->setPos(Window::getWidth() / 2, 340);
	this->addChild(exitBtn);

	// �����������ذ�ť
	soundBtn = gcnew SoundButton();
	// ���ð�ťλ��
	soundBtn->setPos(50, 50);
	this->addChild(soundBtn);

	// �ָ��ڵ�Ĭ�����ĵ�λ��
	Node::setDefaultAnchor(0, 0);
}

void StartScene::onEnter()
{
	// ��ǰ�ؿ���Ϊ 1 ʱ�����Լ�����Ϸ
	if (g_CurrentLevel == 1)
	{
		resumeBtn->setEnable(false);
	}
	else
	{
		resumeBtn->setEnable(true);
	}
	// �������ְ�ť״̬
	soundBtn->updateStatus();
}

void StartScene::Start()
{
	// ���� PlayScene ����
	auto scene = gcnew PlayScene(1);
	// �л��� PlayScene ����
	SceneManager::enter(scene);
}

void StartScene::Continue()
{
	// ���� PlayScene ����
	auto scene = gcnew PlayScene(g_CurrentLevel);
	// �л��� PlayScene ����
	SceneManager::enter(scene);
}

void StartScene::Exit()
{
	// �˳���Ϸ
	Game::quit();
}
