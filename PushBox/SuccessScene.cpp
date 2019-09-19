#include "SuccessScene.h"
#include "PlayScene.h"

SuccessScene::SuccessScene()
{
	// 背景图片
	auto background = gcnew Sprite(L"res/success.jpg");
	this->addChild(background);

	// 回主菜单按钮
	auto backBtn = gcnew Button();
	backBtn->setNormal(gcnew Text(L"回主菜单", Font(L"新宋体", 28, Font::Weight::Bold), Text::Style(Color::Black)));
	backBtn->setMouseOver(gcnew Text(L"回主菜单", Font(L"新宋体", 28, Font::Weight::Bold), Text::Style(Color::Blue)));
	backBtn->setPos(255, 350);
	// 设置匿名回调函数
	backBtn->setClickFunc([]() { SceneManager::back(); });
	this->addChild(backBtn);
}
