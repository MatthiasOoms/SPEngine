#include "FallingEnemyState.h"
#include "GameObject.h"
#include "GameCommands.h"
#include "EnemyComponent.h"
#include "WalkingEnemyState.h"

dae::FallingEnemyState::FallingEnemyState(GameObject* pSelf)
	: EnemyState(pSelf)
	, m_FallSpeed{ 75.f }
	, m_FloorsToFall{ 0 }
{
}

dae::FallingEnemyState::FallingEnemyState(GameObject* pSelf, float speed)
	: EnemyState(pSelf)
	, m_FallSpeed{ speed }
	, m_FloorsToFall{ 0 }
{
}

void dae::FallingEnemyState::Update(float elapsedSec)
{
	// Make FallCommand
	FallCommand fallCommand{ GetEnemy(), m_FallSpeed };
	fallCommand.Execute(elapsedSec);
}

void dae::FallingEnemyState::Render(float) const
{
}

void dae::FallingEnemyState::OnEnter()
{
}

void dae::FallingEnemyState::OnExit()
{
}

void dae::FallingEnemyState::SetFloorsToFall(int floors)
{
	m_FloorsToFall = floors;

	if (m_FloorsToFall <= 0)
	{
		// Go back to WalkingState
		GetEnemy()->GetComponent<EnemyComponent>()->SetState(new WalkingEnemyState{ GetEnemy() });
	}
}
