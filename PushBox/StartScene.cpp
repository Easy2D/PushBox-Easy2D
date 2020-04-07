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

	// ��������
	auto fontNormal = Font(L"������", 28, Font::Weight::Bold);
	auto fontSelect = Font(L"������", 28, Font::Weight::Bold);
	auto fontDisable = Font(L"������", 28, Font::Weight::Bold);

	// ������ʽ
	auto styleNormal = Text::Style(Color::Black);
	auto styleSelect = Text::Style(Color::Blue);
	auto styleDisable = Text::Style(Color::LightGray);

	// ������ʼ��Ϸ��ť
	auto startBtn = gcnew Button();
	startBtn->setNormal(gcnew Text(L"����Ϸ", fontNormal, styleNormal));
	startBtn->setMouseOver(gcnew Text(L"����Ϸ", fontSelect, styleSelect));
	// ���ð�ťλ��
	startBtn->setPos(Window::getWidth() / 2, 260);
	// ���ð�ť�ص�����
	startBtn->setClickFunc(std::bind(&StartScene::Start, this));
	this->addChild(startBtn);

	// ������Ϸ��ť
	resumeBtn = gcnew Button();
	resumeBtn->setNormal(gcnew Text(L"�����ؿ�", fontNormal, styleNormal));
	resumeBtn->setMouseOver(gcnew Text(L"�����ؿ�", fontSelect, styleSelect));
	resumeBtn->setDisabled(gcnew Text(L"�����ؿ�", fontDisable, styleDisable));
	// ���ð�ťλ��
	resumeBtn->setPos(Window::getWidth() / 2, 300);
	// ����ǰ�ؿ��ǵ�һ�أ����������ť
	if (g_CurrentLevel == 1)
	{
		resumeBtn->setEnable(false);
	}
	// ���ð�ť�ص�����
	resumeBtn->setClickFunc(std::bind(&StartScene::Continue, this));
	this->addChild(resumeBtn);

	// �����˳���ť
	auto exitBtn = gcnew Button();
	exitBtn->setNormal(gcnew Text(L"�˳�", fontNormal, styleNormal));
	exitBtn->setMouseOver(gcnew Text(L"�˳�", fontSelect, styleSelect));
	// ���ð�ťλ��
	exitBtn->setPos(Window::getWidth() / 2, 340);
	// ���ð�ť�ص�����
	exitBtn->setClickFunc(std::bind(&StartScene::Exit, this));
	this->addChild(exitBtn);

	// �����������ذ�ť
	soundBtn = gcnew Button(gcnew Sprite(g_SoundOpen ? L"res/soundon.png" : L"res/soundoff.png"));
	// ���ð�ťλ��
	soundBtn->setPos(50, 50);
	// ���ð�ť�ص�����
	soundBtn->setClickFunc(std::bind(&StartScene::Sound, this));
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

void StartScene::Sound()
{
	// ��ȡ��ť״̬
	if (!g_SoundOpen)
	{
		// ������������
		MusicPlayer::resume(L"res/background.wav");
		soundBtn->setNormal(gcnew Sprite(L"res/soundon.png"));
		g_SoundOpen = true;
	}
	else
	{
		// ��ͣ��������
		MusicPlayer::pause(L"res/background.wav");
		soundBtn->setNormal(gcnew Sprite(L"res/soundoff.png"));
		g_SoundOpen = false;
	}
	// ������Ϣ���ļ�
	Data::saveBool(L"sound", g_SoundOpen);
}
