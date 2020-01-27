#include <easy2d/easy2d.h>
using namespace easy2d;

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

	// �򿪻�ر�����
	void Sound();

protected:
	// ��������
	Button* soundBtn;
	// ������Ϸ��ť
	Button* resumeBtn;
};