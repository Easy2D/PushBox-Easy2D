#pragma once
#include "Buttons.h"

class StartScene : 
	public Scene
{
public:
	StartScene();

	// 这个函数在进入场景时自动执行
	void onEnter() override;

	// 新游戏
	void Start();
	// 继续游戏
	void Continue();
	// 退出游戏
	void Exit();

protected:
	// 继续游戏按钮
	MyTextButton* resumeBtn;
	// 音乐开关按钮
	SoundButton* soundBtn;
};