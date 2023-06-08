
#include "InputManager.h"

#include <SDL_events.h>

#include "ICommand.h"

using namespace dae;

InputManager::~InputManager()
{}

bool InputManager::ProcessInput()
{
	bool doContinue = ProcessGamepads();
	doContinue = doContinue and ProcessKeyboard();
	return doContinue;
}


bool InputManager::ProcessGamepads()
{
	bool doContinue = true;

	for (auto& gp : m_Gamepads)
	{
		gp->Update();
	}

	for (auto& [key, command] : m_ButtonMapping)
	{
		unsigned gamepadNr = std::get<0>(key);
		Gamepad::Button button = std::get<Gamepad::Button>(key);
		InputState inputState = std::get<InputState>(key);

		switch (inputState)
		{
		case InputState::Up:
			if (m_Gamepads[gamepadNr]->IsUp(button))
			{
				doContinue = doContinue and command->Execute();
			} break;
		case InputState::Down:
			if (m_Gamepads[gamepadNr]->IsDown(button))
			{
				doContinue &= doContinue and command->Execute();
			} break;
		case InputState::Pressed:
			if (m_Gamepads[gamepadNr]->IsPressed(button))
			{
				doContinue &= doContinue and command->Execute();
			} break;
		}
	}

	return doContinue;
}

bool InputManager::ProcessKeyboard()
{
	bool doContinue = true;

	SDL_Event e{};
	while (SDL_PollEvent(&e) != 0)
	{
		switch (e.type)
		{
		case SDL_QUIT:
			doContinue = false;
			break;
		case SDL_KEYDOWN: {
			auto key = std::make_tuple(e.key.keysym.scancode, InputState::Down);
			if (m_KeyMapping.count(key))
			{
				doContinue = doContinue and m_KeyMapping[key]->Execute();
			}
			break;}
		case SDL_KEYUP: {
			auto key = std::make_tuple(e.key.keysym.scancode, InputState::Up);
			if (m_KeyMapping.count(key))
			{
				doContinue = doContinue and m_KeyMapping[key]->Execute();
			}
			break;}
		}
	}

	const Uint8* state = SDL_GetKeyboardState(nullptr);
	for(auto iter = begin(m_KeyMapping); iter != end(m_KeyMapping); ++iter)
	{
		if(state[std::get<0>(iter->first)] and std::get<1>(iter->first) == InputState::Pressed)
		{
			doContinue = doContinue and iter->second->Execute();
		}
	}

	return doContinue;
}

void InputManager::ButtonBind(unsigned gamepadNr, Gamepad::Button button, InputState buttonState, std::shared_ptr<ICommand> command)
{
	m_ButtonMapping[std::make_tuple(gamepadNr, button, buttonState)] = command;
}


void InputManager::ButtonBind(SDL_Scancode key, InputState keyState, std::shared_ptr<ICommand> command)
{
	m_KeyMapping[std::make_tuple(key, keyState)] = command;
}

unsigned InputManager::AddGamepad()
{
	m_Gamepads.emplace_back(std::make_unique<Gamepad>(static_cast<int>(m_Gamepads.size())));
	return static_cast<unsigned>(m_Gamepads.size() - 1);
}
