#include "SuccessScene.h"
#include "PlayScene.h"

SuccessScene::SuccessScene()
{
	// ����ͼƬ
	auto background = gcnew Sprite("res/success.jpg");
	this->addChild(background);

	// �����˵���ť
	auto backBtn = gcnew Button();
	backBtn->setNormal(gcnew Text("�����˵�", Font("������", 28, Font::Weight::Bold), DrawingStyle(Color::Black)));
	backBtn->setMouseOver(gcnew Text("�����˵�", Font("������", 28, Font::Weight::Bold), DrawingStyle(Color::Blue)));
	backBtn->setPos(255, 350);
	// ���ûص�����
	backBtn->setClickFunc([]()
		{
			SceneManager::back();
		});
	this->addChild(backBtn);
}
