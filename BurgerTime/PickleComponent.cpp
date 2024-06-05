#include "PickleComponent.h"
#include "WalkingEnemyState.h"
#include "EnemyState.h"
#include "GameObject.h"

dae::PickleComponent::PickleComponent(GameObject* pOwner)
	: Component(pOwner)
	, m_pCurrentState{ new WalkingEnemyState{ pOwner } }
{
}

dae::PickleComponent::~PickleComponent()
{
	delete m_pCurrentState;
	m_pCurrentState = nullptr;
}

void dae::PickleComponent::Update(float elapsedSec)
{
	// Update the current state
	m_pCurrentState->Update(elapsedSec);
}

void dae::PickleComponent::Render(float elapsedSec) const
{
	m_pCurrentState->Render(elapsedSec);
}

void dae::PickleComponent::SetState(EnemyState* pState)
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
