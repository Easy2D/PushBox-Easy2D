#include "PlayScene.h"
#include "SuccessScene.h"
#include "Buttons.h"

PlayScene::PlayScene(int level)
{
	// ��������
	auto font = Font("������", 28, Font::Weight::Bold);
	auto font2 = Font("������", 20, Font::Weight::Bold);

	// ��ǰ�ؿ�����
	levelText = gcnew Text("", font);
	levelText->setPos(520, 30);
	this->addChild(levelText);

	// ��ǰ��������
	stepText = gcnew Text("", font2);
	stepText->setPos(520, 100);
	this->addChild(stepText);

	// ��Ѳ�������
	bestText = gcnew Text("", font2);
	bestText->setPos(520, 140);
	this->addChild(bestText);

	// �� ESC �˳���ʾ����
	auto exitText = gcnew Text("��ESC����", font2);
	exitText->setPos(520, 250);
	this->addChild(exitText);

	// ���س����¿�ʼ��ʾ����
	auto restartText = gcnew Text("���س��ؿ�", font2);
	restartText->setPos(520, 290);
	this->addChild(restartText);

	// �������ذ�ť
	auto soundBtn = gcnew SoundButton();
	soundBtn->setPos(520, 330);
	this->addChild(soundBtn);

	// ��ӵ�ͼ����
	mapLayer = gcnew Node();
	this->addChild(mapLayer);

	// ���ùؿ�
	this->SetLevel(level);
}

void PlayScene::onUpdate()
{
	// �� ESC ������һ����
	if (Input::isPress(KeyCode::Esc))
	{
		SceneManager::back();
	}
	// ���س����¿�ʼ
	if (Input::isPress(KeyCode::Enter))
	{
		SetLevel(g_CurrentLevel);
	}

	// �����������ƶ�����
	if (Input::isPress(KeyCode::Up))
	{
		Move(0, -1, 1);
	}
	else if (Input::isPress(KeyCode::Down))
	{
		Move(0, 1, 2);
	}
	else if (Input::isPress(KeyCode::Left))
	{
		Move(-1, 0, 3);
	}
	else if (Input::isPress(KeyCode::Right))
	{
		Move(1, 0, 4);
	}
	else
	{
		// ������������
		return;
	}

	// ˢ�µ�ͼ
	Flush();

	// �ж��Ƿ�ͨ��
	for (int i = 0; i < map.width; i++)
	{
		for (int j = 0; j < map.height; j++)
		{
			Piece p = map.value[j][i];
			if (p.type == TYPE::Box && p.isPoint == false)
			{
				// ����δ���ڵ÷ֵ��ϵ����ӣ���δͨ��
				return;
			}
		}
	}

	// ���������Ӷ��ڵ÷ֵ��ϣ�������һ��
	GameOver();
}

void PlayScene::Flush()
{
	// ���ԭ��ͼ
	mapLayer->removeAllChildren();
	// ���ص�ͼ
	for (int i = 0; i < map.width; i++)
	{
		for (int j = 0; j < map.height; j++)
		{
			// ȡ����ͼ�е�Ԫ��
			Piece piece = map.value[j][i];
			// ��������
			auto sprite = gcnew Sprite();

			// ���ݲ�ͬ���ͼ��ز�ͬͼƬ
			// 1.ǽ
			if (piece.type == TYPE::Wall)
			{
				sprite->open("res/wall.gif");
			}
			// 2.�÷ֵ㴦�ĵ���
			else if (piece.type == TYPE::Ground && piece.isPoint)
			{
				sprite->open("res/point.gif");
			}
			// 3.��ͨ����
			else if (piece.type == TYPE::Ground)
			{
				sprite->open("res/floor.gif");
			}
			// 4.�÷ֵ㴦������
			else if (piece.type == TYPE::Box && piece.isPoint)
			{
				sprite->open("res/boxinpoint.gif");
			}
			// 5.��ͨ����
			else if (piece.type == TYPE::Box)
			{
				sprite->open("res/box.gif");
			}
			// 6.���������ӵĽ�ɫ
			else if (piece.type == TYPE::Man && g_Pushing)
			{
				// �������������ĸ�������ز�ͬͼƬ
				switch (g_Direct)
				{
				case 1:
					sprite->open("res/manhandup.gif");
					break;
				case 2:
					sprite->open("res/manhanddown.gif");
					break;
				case 3:
					sprite->open("res/manhandleft.gif");
					break;
				case 4:
					sprite->open("res/manhandright.gif");
					break;
				}
			}
			// 7.��ͨ��ɫ
			else if (piece.type == TYPE::Man)
			{
				switch (g_Direct)
				{
				case 1:
					sprite->open("res/manup.gif");
					break;
				case 2:
					sprite->open("res/mandown.gif");
					break;
				case 3:
					sprite->open("res/manleft.gif");
					break;
				case 4:
					sprite->open("res/manright.gif");
					break;
				}
			}
			else
			{
				continue;
			}
			// ����ͼƬλ��
			sprite->setPosX(((12 - map.width) / 2 + i) * sprite->getWidth());
			sprite->setPosY(((12 - map.height) / 2 + j) * sprite->getHeight());
			// ��ʾ����ͼƬ
			mapLayer->addChild(sprite);
		}
	}
}

void PlayScene::SetLevel(int level)
{
	// ����ؿ��ȼ�
	::g_CurrentLevel = level;
	// ����ؿ���Ϣ���ļ�
	Data::saveInt("level", ::g_CurrentLevel);
	// �޸Ĺؿ���Ϣ����
	levelText->setText("��" + std::to_string(level) + "��");

	// ���ò���
	SetStep(0);
	// ��ȡ��Ѳ���
	String strLevel = "level" + std::to_string(level);
	int bestStep = Data::getInt(strLevel, 0);
	if (bestStep != 0)
	{
		bestText->setText("���" + std::to_string(bestStep) + "��");
	}
	else
	{
		bestText->setText("");
	}

	// ��ȡ�ؿ���ͼ��Ϣ
	map = g_Maps[level - 1];
	// ��ʼ����ɫ��Ϣ����ɫ������
	g_Direct = 2;
	// ��ɫ��������
	g_Pushing = false;
	// �����ͼ
	Flush();
}

void PlayScene::Move(int x, int y, int direct)
{
	// �ӵ�ͼ��ȡ����ɫ
	Piece role = map.value[map.roleY][map.roleX];
	x = x + map.roleX;
	y = y + map.roleY;
	g_Direct = direct;

	// ����ͬ���
	// 1. ǰ����ǽ
	if (map.value[y][x].type == TYPE::Wall)
	{
		return;	// ʲô������
	}
	// 2. ǰ���ǵ���
	else if (map.value[y][x].type == TYPE::Ground)
	{
		// ��ɫ����������
		g_Pushing = false;
		// ����ɫ��ǰ���ƶ�һ��
		map.value[map.roleY][map.roleX].type = TYPE::Ground;
		map.value[y][x].type = TYPE::Man;
		// ������Ч
		if (::g_SoundOpen) MusicPlayer::play("res/manmove.wav");
	}
	// 3.ǰ��������
	else if (map.value[y][x].type == TYPE::Box)
	{
		// ��ɫ����������
		g_Pushing = true;
		// ���ݽ�ɫ�����ж�����ǰ���ǲ���ǽ
		int boxX = 0, boxY = 0;
		if (g_Direct == 1)
		{
			boxX = x;
			boxY = y - 1;
		}
		else if (g_Direct == 2)
		{
			boxX = x;
			boxY = y + 1;
		}
		else if (g_Direct == 3)
		{
			boxX = x - 1;
			boxY = y;
		}
		else if (g_Direct == 4)
		{
			boxX = x + 1;
			boxY = y;
		}
		// ����ǰ����ǽ�������ӾͲ��ƶ�
		if (map.value[boxY][boxX].type == TYPE::Wall ||
			map.value[boxY][boxX].type == TYPE::Box)
			return;
		// ����ǰ������ǽ����ͬʱ�ƶ����Ӻͽ�ɫ
		map.value[boxY][boxX].type = TYPE::Box;
		map.value[y][x].type = TYPE::Man;
		map.value[map.roleY][map.roleX].type = TYPE::Ground;
		// ������Ч
		if (::g_SoundOpen) MusicPlayer::play("res/boxmove.wav");
	}
	// ���±����ɫλ��
	map.roleX = x;
	map.roleY = y;
	// ������һ
	SetStep(step + 1);
}

void PlayScene::SetStep(int step)
{
	// ���沽��
	this->step = step;
	// �޸Ĳ�������
	stepText->setText("��ǰ" + std::to_string(step) + "��");
}

void PlayScene::GameOver()
{
	// ��ȡ��Ѳ���
	String strLevel = "level" + std::to_string(g_CurrentLevel);
	int bestStep = Data::getInt(strLevel, 0);
	// ���±�����Ѳ���
	if (bestStep == 0 || step < bestStep)
	{
		Data::saveInt(strLevel, step);
	}
	// ���Ѿ������һ�أ���ʾͨ�ؽ���
	if (::g_CurrentLevel == MAX_LEVEL)
	{
		auto successScene = gcnew SuccessScene;
		// ���������� false ��ʾ�����ٷ��ص�ǰ����
		SceneManager::enter(successScene, nullptr, false);
		return;
	}
	// ������һ��
	SetLevel(::g_CurrentLevel + 1);
}
