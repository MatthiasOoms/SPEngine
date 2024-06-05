#include "EggComponent.h"
#include "WalkingEnemyState.h"
#include "EnemyState.h"
#include "GameObject.h"

dae::EggComponent::EggComponent(GameObject* pOwner)
	: Component(pOwner)
	, m_pCurrentState{ new WalkingEnemyState{ pOwner } }
{
}

dae::EggComponent::~EggComponent()
{
	delete m_pCurrentState;
	m_pCurrentState = nullptr;
}

void dae::EggComponent::Update(float elapsedSec)
{
	// Update the current state
	m_pCurrentState->Update(elapsedSec);
}

void dae::EggComponent::Render(float elapsedSec) const
{
	m_pCurrentState->Render(elapsedSec);
}

void dae::EggComponent::SetState(EnemyState* pState)
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
