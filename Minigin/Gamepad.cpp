#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>
#pragma comment(lib, "xinput.lib")

#include "Gamepad.h"

using namespace dae;

class Gamepad::GamepadImpl
{
public:
	GamepadImpl(int gamepadIndex) : _gamepadIndex{gamepadIndex}
	{
		ZeroMemory(&previousState, sizeof(XINPUT_STATE));
		ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	}

	void Update()
	{
		CopyMemory(&previousState, &currentState, sizeof(XINPUT_STATE));
		ZeroMemory(&currentState, sizeof(XINPUT_STATE));
		XInputGetState(_gamepadIndex, &currentState);

		const auto buttonChanges = currentState.Gamepad.wButtons ^ previousState.Gamepad.wButtons;
		buttonsPressedThisFrame = buttonChanges & currentState.Gamepad.wButtons;
		buttonsReleasedThisFrame = buttonChanges & (~currentState.Gamepad.wButtons);
	}

	bool IsDownThisFrame(unsigned int button) const { return buttonsPressedThisFrame & button; }
	bool IsUpThisFrame(unsigned int button) const  { return buttonsReleasedThisFrame & button; }
	bool IsPressed(unsigned int button) const { return currentState.Gamepad.wButtons & button; }

private:
	XINPUT_STATE previousState{};
	XINPUT_STATE currentState{};

	WORD buttonsPressedThisFrame{};
	WORD buttonsReleasedThisFrame{};

	int _gamepadIndex;
};

Gamepad::Gamepad(int gamepadIndex)
{
	pImpl = new GamepadImpl(gamepadIndex);
}

Gamepad::~Gamepad()
{
	delete pImpl;
}

void Gamepad::Update()
{
	pImpl->Update();
}

bool Gamepad::IsDown(Button button) const
{
	return pImpl->IsDownThisFrame(static_cast<unsigned int>(button));
}

bool Gamepad::IsUp(Button button) const
{
	return pImpl->IsUpThisFrame(static_cast<unsigned int>(button));
}

bool Gamepad::IsPressed(Button button) const
{
	return pImpl->IsPressed(static_cast<unsigned int>(button));
}
