#pragma once
#include "Buttons.h"

class StartScene : 
	public Scene
{
public:
	StartScene();

	// ��������ڽ��볡��ʱ�Զ�ִ��
	void onEnter() override;

	// ����Ϸ
	void Start();
	// ������Ϸ
	void Continue();
	// �˳���Ϸ
	void Exit();

protected:
	// ������Ϸ��ť
	MyTextButton* resumeBtn;
	// ���ֿ��ذ�ť
	SoundButton* soundBtn;
};