#include "SuccessScene.h"
#include "PlayScene.h"

SuccessScene::SuccessScene()
{
	// ����ͼƬ
	auto background = gcnew Sprite(L"res/success.jpg");
	this->addChild(background);

	// �����˵���ť
	auto backBtn = gcnew Button();
	backBtn->setNormal(gcnew Text(L"�����˵�", Font(L"������", 28, Font::Weight::Bold), Text::Style(Color::Black)));
	backBtn->setMouseOver(gcnew Text(L"�����˵�", Font(L"������", 28, Font::Weight::Bold), Text::Style(Color::Blue)));
	backBtn->setPos(255, 350);
	// ���������ص�����
	backBtn->setClickFunc([]() { SceneManager::back(); });
	this->addChild(backBtn);
}
