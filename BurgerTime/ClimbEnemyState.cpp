#include "ClimbEnemyState.h"
#include "GameCommands.h"
#include "GameObject.h"
#include <SceneManager.h>
#include <Scene.h>


dae::ClimbEnemyState::ClimbEnemyState(GameObject* pPlayer, float speed)
	: EnemyState(pPlayer)
	, m_Speed{ speed }
{
}

void dae::ClimbEnemyState::Update(float elapsedSec)
{
	// Get the enemy's position
	const auto enemyPos{ GetEnemy()->GetTransform().GetWorldPosition() };

	// Start climbing the ladder
	dae::ClimbCommand climbCommand{ GetEnemy(), m_Speed };
	climbCommand.Execute(elapsedSec);
}

void dae::ClimbEnemyState::Render(float)
{
}

void dae::ClimbEnemyState::OnEnter()
{
}

void dae::ClimbEnemyState::OnExit()
{
}