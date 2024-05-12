#pragma once

// TODO : Use Include guards instead of #pragma once

#include "Singleton.h"
#include "Controller.h"
#include "Command.h"
#include "SceneManager.h"
#include <vector>
#include <memory>
#include <map>
#include <SDL_scancode.h>
#include <string>

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
	private:
		// ControllerKey = <ControllerIndex, Button>
		using ControllerKey = std::pair<unsigned int, Controller::ControllerButton>;
		using ControllerKeyState = std::pair<ControllerKey, keyState>;
		using ControllerCommandsMap = std::map<ControllerKeyState, std::unique_ptr<Command>>;
		using SceneControllerCommandsMap = std::map<std::string, ControllerCommandsMap>;

		using KeyboardKey = std::pair<SDL_Scancode, keyState>;
		using KeyboardCommandsMap = std::map<KeyboardKey, std::unique_ptr<Command>>;
		using SceneKeyboardCommandsMap = std::map<std::string, KeyboardCommandsMap>;

		SceneControllerCommandsMap m_ConsoleCommands{};
		ControllerCommandsMap m_GlobalConsoleCommands{};
		SceneKeyboardCommandsMap m_KeyboardCommands{};
		KeyboardCommandsMap m_GlobalKeyboardCommands{};
		std::vector<std::unique_ptr<Controller>> m_Controllers{};

		std::vector<Uint8> m_pPreviousKeyState{ std::vector<Uint8>(SDL_NUM_SCANCODES) };
		std::vector<Uint8> m_pCurrentPressed{ std::vector<Uint8>(SDL_NUM_SCANCODES) };

		const int m_MaxControllers{ 4 };

		dae::SceneManager& m_pSceneManager{ SceneManager::GetInstance() };

	public:
		bool ProcessInput(float elapsedSec);
		bool IsKeyPressed(SDL_Scancode key);

		int AddController();
		int AddControllersMax();

		void AddCommand(std::string sceneName, int controllerIdx, Controller::ControllerButton button, keyState state, std::unique_ptr<Command> pCommand);
		void AddCommand(std::string sceneName, SDL_Scancode key, keyState state, std::unique_ptr<Command> pCommand);
		void RemoveCommand(std::string sceneName, int controllerIdx, Controller::ControllerButton button, keyState state);
		void RemoveCommand(std::string sceneName, SDL_Scancode key, keyState state);

		void AddGlobalCommand(int controllerIdx, Controller::ControllerButton button, keyState state, std::unique_ptr<Command> pCommand);
		void AddGlobalCommand(SDL_Scancode key, keyState state, std::unique_ptr<Command> pCommand);
		void RemoveGlobalCommand(int controllerIdx, Controller::ControllerButton button, keyState state);
		void RemoveGlobalCommand(SDL_Scancode key, keyState state);
	};

}
