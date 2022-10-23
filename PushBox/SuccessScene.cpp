#include "SuccessScene.h"
#include "PlayScene.h"

SuccessScene::SuccessScene()
{
	// 背景图片
	auto background = gcnew Sprite("res/success.jpg");
	this->addChild(background);

	// 回主菜单按钮
	auto backBtn = gcnew Button();
	backBtn->setNormal(gcnew Text("回主菜单", Font("新宋体", 28, Font::Weight::Bold), DrawingStyle(Color::Black)));
	backBtn->setMouseOver(gcnew Text("回主菜单", Font("新宋体", 28, Font::Weight::Bold), DrawingStyle(Color::Blue)));
	backBtn->setPos(255, 350);
	// 设置回调函数
	backBtn->setClickFunc([]()
		{
			SceneManager::back();
		});
	this->addChild(backBtn);
}
