#pragma once

// TODO : Use Include guards instead of #pragma once

#include "Singleton.h"
#include "Controller.h"
#include "Command.h"
#include <vector>
#include <memory>
#include <map>
#include <SDL_scancode.h>

namespace dae
{
	enum struct keyState
	{
		isDown,		// Down this frame
		isHeld,		// Held this frame
		isUp		// Released this frame
	};

	class InputManager final : public Singleton<InputManager>
	{
		// ControllerKey = <ControllerIndex, Button>
		using ControllerKey = std::pair<unsigned int, Controller::ControllerButton>;
		using ControllerKeyState = std::pair<ControllerKey, keyState>;
		using ControllerCommandsMap = std::map<ControllerKeyState, std::unique_ptr<Command>>;

		using KeyboardKey = std::pair<SDL_Scancode, keyState>;
		using KeyboardCommandsMap = std::map<KeyboardKey, std::unique_ptr<Command>>;

		ControllerCommandsMap m_ConsoleCommands{};
		KeyboardCommandsMap m_KeyboardCommands{};
		std::vector<std::unique_ptr<Controller>> m_Controllers{};

		std::vector<Uint8> m_pPreviousKeyState{ std::vector<Uint8>(SDL_NUM_SCANCODES) };

		const int m_MaxControllers{ 4 };

	public:
		bool ProcessInput(float elapsedSec);

		int AddController();
		int AddControllersMax();
		void AddCommand(int controllerIdx, Controller::ControllerButton button, keyState state, std::unique_ptr<Command> pCommand);
		void AddCommand(SDL_Scancode key, keyState state, std::unique_ptr<Command> pCommand);
		void RemoveCommand(int controllerIdx, Controller::ControllerButton button, keyState state);
		void RemoveCommand(SDL_Scancode key, keyState state);
	};

}
