#pragma once
#include <memory>
#include <vector>
#include <map>
#include <SDL_scancode.h>

#include "ICommand.h"
#include "Gamepad.h"
#include "Singleton.h"

namespace dae
{
	class Gamepad;
	class ICommand;
	class InputManager final : public Singleton<InputManager>
	{
	public:
		enum class InputState
		{
			Up,
			Down,
			Pressed
		};

		~InputManager();
		bool ProcessInput();
		void ButtonBind(unsigned gamepadNr, Gamepad::Button button, InputState buttonState, std::shared_ptr<ICommand> command);
		void ButtonBind(SDL_Scancode key, InputState keyState, std::shared_ptr<ICommand> command);
		unsigned AddGamepad();


	private:
		bool ProcessKeyboard();
		bool ProcessGamepads();

		using GamepadInput = std::tuple<unsigned, Gamepad::Button, InputState>;
		using KeyboardInput = std::tuple<SDL_Scancode, InputState>;
		std::map<GamepadInput, std::shared_ptr<ICommand>> m_ButtonMapping{};
		std::map<KeyboardInput, std::shared_ptr<ICommand>> m_KeyMapping{};
		std::vector<std::unique_ptr<Gamepad>> m_Gamepads{};
	};

}
