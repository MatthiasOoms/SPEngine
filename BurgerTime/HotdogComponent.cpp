#include "HotdogComponent.h"
#include "WalkingEnemyState.h"
#include "EnemyState.h"
#include "GameObject.h"

dae::HotdogComponent::HotdogComponent(GameObject* pOwner)
	: Component(pOwner)
	, m_pCurrentState{ new WalkingEnemyState{ pOwner } }
{
}

dae::HotdogComponent::~HotdogComponent()
{
	delete m_pCurrentState;
	m_pCurrentState = nullptr;
}

void dae::HotdogComponent::Update(float elapsedSec)
{
	// Update the current state
	m_pCurrentState->Update(elapsedSec);
}

void dae::HotdogComponent::Render(float elapsedSec) const
{
	m_pCurrentState->Render(elapsedSec);
}

void dae::HotdogComponent::SetState(EnemyState* pState)
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
