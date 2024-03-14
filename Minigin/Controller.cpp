#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#include "Controller.h"

#pragma comment(lib, "xinput.lib")

namespace dae
{
	class Controller::ControllerImpl final
	{
		XINPUT_STATE m_PreviousState{};
		XINPUT_STATE m_CurrentState{};

		WORD m_ButtonsPressedThisFrame{};
		WORD m_ButtonsReleasedThisFrame{};

		unsigned int m_ControllerIdx;

	public:
		ControllerImpl(unsigned int controllerIdx)
			: m_ControllerIdx{ controllerIdx }
		{
			ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
			ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		}

		void Update()
		{
			CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
			ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
			XInputGetState(m_ControllerIdx, &m_CurrentState);

			auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
			m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
			m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
		}

		unsigned int GetIdx()
		{
			return m_ControllerIdx;
		}

		bool IsDownThisFrame(unsigned int button) const { return m_ButtonsPressedThisFrame & button; };
		bool IsUpThisFrame(unsigned int button) const { return m_ButtonsReleasedThisFrame & button; };
		bool IsPressed(unsigned int button) const { return m_CurrentState.Gamepad.wButtons & button; };
	};

	Controller::Controller(unsigned int controllerIdx)
	{
		pImpl = new ControllerImpl{ controllerIdx };
	}

	Controller::~Controller()
	{
		delete pImpl;
		pImpl = nullptr;
	}

	void Controller::Update()
	{
		pImpl->Update();
	}

	unsigned int Controller::GetIdx() const
	{
		return pImpl->GetIdx();
	}

	bool Controller::IsDown(ControllerButton button) const
	{
		return pImpl->IsDownThisFrame(static_cast<unsigned int>(button));
	}

	bool Controller::IsUp(ControllerButton button) const
	{
		return pImpl->IsUpThisFrame(static_cast<unsigned int>(button));
	}

	bool Controller::IsPressed(ControllerButton button) const
	{
		return pImpl->IsPressed(static_cast<unsigned int>(button));
	}
}