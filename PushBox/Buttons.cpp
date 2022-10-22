#include "Buttons.h"
#include "Data.h"

static DrawingStyle buttonNormalStyle = DrawingStyle(Color::Black);
static DrawingStyle buttonHighlightStyle = DrawingStyle(Color::Blue);
static DrawingStyle buttonDisabledStyle = DrawingStyle(Color::LightGray);

MyTextButton::MyTextButton(const String& text, Function<void()> callback)
{
	this->setText(text);
	this->setFont(Font(L"新宋体", 28, Font::Weight::Bold));
	this->setDrawingStyle(buttonNormalStyle);

	// 添加按钮监听器
	auto lis = gcnew ButtonListener([=](ButtonEvent evt) {
		if (enabled) {
			if (evt == ButtonEvent::MouseEntered) {
				// 鼠标放在按钮上，变色
				this->setDrawingStyle(buttonHighlightStyle);
			}
			if (evt == ButtonEvent::MouseExited) {
				// 鼠标移出按钮，恢复颜色
				this->setDrawingStyle(buttonNormalStyle);
			}
			if (evt == ButtonEvent::Clicked) {
				// 点击鼠标
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
				// 继续背景音乐
				MusicPlayer::resume(sound);
			}
			else
			{
				// 暂停背景音乐
				MusicPlayer::pause(sound);
			}
			g_SoundOpen = state;
			this->setState(state);
			// 保存信息到文件
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
