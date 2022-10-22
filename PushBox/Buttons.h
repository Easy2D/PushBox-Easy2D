#pragma once
#include <easy2d/easy2d.h>
using namespace easy2d;

class MyTextButton : public Text
{
public:
	MyTextButton(const String& text, Function<void()> callback);

	void setEnable(bool enable);

private:
	bool enabled = true;
};

class SoundButton : public Sprite
{
public:
	SoundButton();

	void updateStatus();

private:
	void setState(bool state);

	ToggleButtonListener* lis = nullptr;
};
