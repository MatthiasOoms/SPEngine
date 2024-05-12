#include "PlayerComponent.h"
#include "IdlePlayerState.h"
#include "PlayerState.h"
#include "GameObject.h"

dae::PlayerComponent::PlayerComponent(GameObject* pOwner)
	: Component(pOwner)
	, m_pCurrentState{ new IdlePlayerState{ pOwner } }
{
}

dae::PlayerComponent::~PlayerComponent()
{
	delete m_pCurrentState;
	m_pCurrentState = nullptr;
}

void dae::PlayerComponent::Update(float elapsedSec)
{
	m_pCurrentState->Update(elapsedSec);
}

void dae::PlayerComponent::Render(float elapsedSec) const
{
	m_pCurrentState->Render(elapsedSec);
}

void dae::PlayerComponent::SetState(PlayerState* pState)
{
	if (pState != nullptr)
	{
		if (m_pCurrentState)
		{
			m_pCurrentState->OnExit();
			delete m_pCurrentState;
		}
		m_pCurrentState = pState;
		m_pCurrentState->OnEnter();
	}
}
