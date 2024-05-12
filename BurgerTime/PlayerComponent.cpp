#include "PlayerComponent.h"
#include "PlayerState.h"
#include "GameObject.h"

dae::PlayerComponent::PlayerComponent(GameObject* pOwner)
	: Component(pOwner)
{
}

dae::PlayerComponent::~PlayerComponent()
{
	delete m_pCurrentState;
	m_pCurrentState = nullptr;
}

void dae::PlayerComponent::Update(float elapsedSec)
{
	auto newState = m_pCurrentState->HandleState(elapsedSec);

	if (newState != nullptr)
	{
		m_pCurrentState->OnExit();

		delete m_pCurrentState;
		m_pCurrentState = nullptr;

		m_pCurrentState = newState;
		m_pCurrentState->OnEnter();
	}
}

void dae::PlayerComponent::Render(float elapsedSec) const
{
	m_pCurrentState->Render(elapsedSec);
}
