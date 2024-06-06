#include "EnemyComponent.h"
#include "WalkingEnemyState.h"
#include "EnemyState.h"
#include "GameObject.h"

dae::EnemyComponent::EnemyComponent(GameObject* pOwner)
	: Component(pOwner)
	, m_pCurrentState{ new WalkingEnemyState{ pOwner } }
	, m_Type{ EnemyType::Hotdog }
{
}

dae::EnemyComponent::~EnemyComponent()
{
	delete m_pCurrentState;
	m_pCurrentState = nullptr;
}

void dae::EnemyComponent::Update(float elapsedSec)
{
	// Update the current state
	m_pCurrentState->Update(elapsedSec);
}

void dae::EnemyComponent::Render(float elapsedSec) const
{
	m_pCurrentState->Render(elapsedSec);
}

void dae::EnemyComponent::SetState(EnemyState* pState)
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

void dae::EnemyComponent::SetType(EnemyType type)
{
	m_Type = type;
}
