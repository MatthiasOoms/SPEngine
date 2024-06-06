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
	// I am already touching a ladder because I am in the ClimbState
	// If the any ladder is below me, I will start climbing it
	// If the any ladder is above me, I will start climbing it

	// For every ladder
	for (auto ladder : dae::SceneManager::GetInstance().GetActiveScene().GetObjectsByTag("Ladder"))
	{
		// Get the ladder's position
		const auto ladderPos{ ladder->GetTransform().GetWorldPosition() };

		// Get the enemy's position
		const auto enemyPos{ GetEnemy()->GetTransform().GetWorldPosition() };

		// If the ladder is below me
		if (ladderPos.y < enemyPos.y)
		{
			// Start climbing the ladder
			dae::ClimbCommand climbCommand{ GetEnemy(), 75 };
			climbCommand.Execute(elapsedSec);
		}
		// If the ladder is above me
		else if (ladderPos.y > enemyPos.y)
		{
			// Start climbing the ladder
			dae::ClimbCommand climbCommand{ GetEnemy(), -75 };
			climbCommand.Execute(elapsedSec);
		}
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