#include "Buttons.h"
#include "Data.h"

static DrawingStyle buttonNormalStyle = DrawingStyle(Color::Black);
static DrawingStyle buttonHighlightStyle = DrawingStyle(Color::Blue);
static DrawingStyle buttonDisabledStyle = DrawingStyle(Color::LightGray);

MyTextButton::MyTextButton(const String& text, Function<void()> callback)
{
	this->setText(text);
	this->setFont(Font(L"������", 28, Font::Weight::Bold));
	this->setDrawingStyle(buttonNormalStyle);

	// ��Ӱ�ť������
	auto lis = gcnew ButtonListener([=](ButtonEvent evt) {
		if (enabled) {
			if (evt == ButtonEvent::MouseEntered) {
				// �����ڰ�ť�ϣ���ɫ
				this->setDrawingStyle(buttonHighlightStyle);
			}
			if (evt == ButtonEvent::MouseExited) {
				// ����Ƴ���ť���ָ���ɫ
				this->setDrawingStyle(buttonNormalStyle);
			}
			if (evt == ButtonEvent::Clicked) {
				// ������
				callback();
			}
		}
		});
	this->addListener(lis);
}

void MyTextButton::setEnable(bool enable)
{
	this->enabled = enable;
	if (!enable)
	{
		this->setDrawingStyle(buttonDisabledStyle);
	}
	else
	{
		this->setDrawingStyle(buttonNormalStyle);
	}
}

SoundButton::SoundButton()
{
	static auto sound = L"res/background.wav";

	lis = gcnew ToggleButtonListener(g_SoundOpen, [=](ButtonEvent evt, bool state) {
		if (evt == ButtonEvent::Clicked) {
			if (state)
			{
				// ������������
				MusicPlayer::resume(sound);
			}
			else
			{
				// ��ͣ��������
				MusicPlayer::pause(sound);
			}
			g_SoundOpen = state;
			this->setState(state);
			// ������Ϣ���ļ�
			Data::saveBool(L"sound", g_SoundOpen);
		}
		});
	this->addListener(lis);
	this->updateStatus();
}

void SoundButton::updateStatus()
{
	this->setState(g_SoundOpen);
	lis->setState(g_SoundOpen);
}

void SoundButton::setState(bool state)
{
	static auto soundon = L"res/soundon.png";
	static auto soundoff = L"res/soundoff.png";
	this->open(state ? soundon : soundoff);
}
