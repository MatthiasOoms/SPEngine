#include "ClimbEnemyState.h"
#include "GameCommands.h"
#include "GameObject.h"
#include <SceneManager.h>
#include <Scene.h>
#include "EnemyComponent.h"
#include "WalkingEnemyState.h"

dae::ClimbEnemyState::ClimbEnemyState(GameObject* pPlayer, GameObject* pLadder, float speed)
	: EnemyState(pPlayer)
	, m_pLadder{ pLadder }
	, m_Speed{ speed }
{
}

void dae::ClimbEnemyState::Update(float elapsedSec)
{
	// Check if the enemy is touching the ladder
	bool touchingLadder{ false };

	// Get the enemy's position
	const auto enemyPos{ GetEnemy()->GetTransform().GetWorldPosition() };
	const auto enemySize{ GetEnemy()->GetTransform().GetDimensions() };

	// Get the ladder's position
	const auto ladderPos{ m_pLadder->GetTransform().GetWorldPosition() };
	const auto ladderSize{ m_pLadder->GetTransform().GetDimensions() };

	// If enemy center is within ladder bounds
	if (enemyPos.x + (enemySize.x / 2) >= ladderPos.x && enemyPos.x + (enemySize.x / 2) <= ladderPos.x + ladderSize.x)
	{
		// If enemy bottom is above ladder bottom and below ladder top
		if (enemyPos.y + enemySize.y <= ladderPos.y + ladderSize.y && enemyPos.y + enemySize.y >= ladderPos.y)
		{
			touchingLadder = true;
		}
	}

	if (touchingLadder)
	{
		// Start climbing the ladder
		dae::ClimbCommand climbCommand{ GetEnemy(), m_Speed };
		climbCommand.Execute(elapsedSec);
	}
	else
	{
		// Make StartWalkCommand
		ClimbEndCommand climbEndCommand{ GetEnemy() };
		climbEndCommand.Execute(elapsedSec);
	}
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