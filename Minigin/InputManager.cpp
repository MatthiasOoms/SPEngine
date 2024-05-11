#include <SDL.h>
#include <functional>
#include <algorithm>
#include "InputManager.h"
#include "SceneManager.h"
#include "Scene.h"

bool dae::InputManager::ProcessInput(float elapsedSec)
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT) 
		{
			return false;
		}
	}

	int size{};
	auto pCurrentKeyState = SDL_GetKeyboardState(&size);

	// Held this frame
	std::vector<Uint8> myCurrentState{ pCurrentKeyState, pCurrentKeyState + size };
	// Held last frame
	std::vector<Uint8> myPreviousState{ m_pPreviousKeyState.begin(), m_pPreviousKeyState.end() };

	std::vector<Uint8> myChangedState(myCurrentState.size()); // For calculations
	std::vector<Uint8> myPressedState(myCurrentState.size()); // Pressed this frame
	std::vector<Uint8> myReleasedState(myCurrentState.size()); // Released this frame

	std::transform(myCurrentState.begin(), myCurrentState.end(), myPreviousState.begin(), myChangedState.begin(), std::bit_xor<Uint8>());
	std::transform(myCurrentState.begin(), myCurrentState.end(), myChangedState.begin(), myPressedState.begin(), std::bit_and<Uint8>());
	std::transform(myCurrentState.begin(), myCurrentState.end(), myChangedState.begin(), myReleasedState.begin(),
		[](Uint8 currentKey, Uint8 changedKey)
		{
			return static_cast<Uint8>(changedKey & (~currentKey));
		}
	);

	auto& sceneManager{ SceneManager::GetInstance() };
	auto sceneName{ sceneManager.GetActiveScene()->GetName() };
	for (auto const& command : m_KeyboardCommands[sceneName])
	{
		if (myPressedState[command.first.first])
		{
			if (command.first.second == keyState::isDown)
			{
				command.second->Execute(elapsedSec);
			}
		}

		if (pCurrentKeyState[command.first.first])
		{
			if (command.first.second == keyState::isHeld)
			{
				command.second->Execute(elapsedSec);
			}
		}

		if (myReleasedState[command.first.first])
		{
			if (command.first.second == keyState::isUp)
			{
				command.second->Execute(elapsedSec);
			}
		}
	}

	for (auto const& controller : m_Controllers)
	{
		controller->Update();
		for (auto const& command : m_ConsoleCommands[sceneName])
		{
			if (command.first.first.first == controller->GetIdx())
			{
				switch (command.first.second)
				{
				case keyState::isDown:
				{
					if (controller->IsDown(command.first.first.second))
					{
						command.second->Execute(elapsedSec);
					}
					break;
				}
				case keyState::isHeld:
				{
					if (controller->IsPressed(command.first.first.second))
					{
						command.second->Execute(elapsedSec);
					}
					break;
				}
				case keyState::isUp:
				{
					if (controller->IsUp(command.first.first.second))
					{
						command.second->Execute(elapsedSec);
					}
					break;
				}
				}
			}
		}
	}

	m_pPreviousKeyState = std::move(myCurrentState);

	return true;
}

int dae::InputManager::AddController()
{
	if (static_cast<int>(m_Controllers.size()) < m_MaxControllers)
	{
		m_Controllers.push_back(std::make_unique<Controller>(static_cast<int>(m_Controllers.size())));
	}
	return static_cast<int>(m_Controllers.size());
}

int dae::InputManager::AddControllersMax()
{
	for (int i{}; i < m_MaxControllers; ++i)
	{
		if (static_cast<int>(m_Controllers.size()) < m_MaxControllers)
		{
			m_Controllers.push_back(std::make_unique<Controller>(static_cast<int>(m_Controllers.size())));
		}
	}
	return static_cast<int>(m_Controllers.size());
}

void dae::InputManager::AddCommand(std::string sceneName, int controllerIdx, Controller::ControllerButton button, keyState state, std::unique_ptr<Command> pCommand)
{
	ControllerKey keyPair{ std::make_pair(controllerIdx, button) };
	ControllerKeyState statePair{ std::make_pair(keyPair, state) };
	m_ConsoleCommands[sceneName].insert(std::make_pair(statePair, std::move(pCommand)));
}

void dae::InputManager::AddCommand(std::string sceneName, SDL_Scancode key, keyState state, std::unique_ptr<Command> pCommand)
{
	KeyboardKey keyPair = std::make_pair(key, state);
	m_KeyboardCommands[sceneName][keyPair] = std::move(pCommand);
}

void dae::InputManager::RemoveCommand(std::string sceneName, int controllerIdx, Controller::ControllerButton button, keyState state)
{
	ControllerKey keyPair{ std::make_pair(controllerIdx, button) };
	ControllerKeyState statePair{ std::make_pair(keyPair, state) };
	m_ConsoleCommands[sceneName].erase(statePair);
}

void dae::InputManager::RemoveCommand(std::string sceneName, SDL_Scancode key, keyState state)
{
	KeyboardKey keyPair = std::make_pair(key, state);
	m_KeyboardCommands[sceneName].erase(keyPair);
}
