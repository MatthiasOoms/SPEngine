#include "WalkingEnemyState.h"
#include "GameCommands.h"
#include "GameObject.h"
#include <SceneManager.h>
#include <Scene.h>
#include "ClimbEnemyState.h"
#include <stdexcept>
#include "EnemyComponent.h"

dae::WalkingEnemyState::WalkingEnemyState(GameObject* pPlayer)
	: EnemyState(pPlayer)
	, m_Speed{ 75 }
	, m_AccumulatedTime{ 0 }
	, m_TimeToClimb{ 1.f }
{
}

dae::WalkingEnemyState::WalkingEnemyState(GameObject* pPlayer, float speed)
	: EnemyState(pPlayer)
	, m_Speed{ speed }
	, m_AccumulatedTime{ 0 }
	, m_TimeToClimb{ 1.f }
{
}

void dae::WalkingEnemyState::Update(float elapsedSec)
{
	// If enemy is controlled, do not update
	if (GetEnemy()->GetComponent<EnemyComponent>()->GetIsControlled())
	{
		return;
	}

	// Update AccumulatedTime
	m_AccumulatedTime += elapsedSec;

	// Get the enemy's position
	const auto enemyPos{ GetEnemy()->GetTransform().GetWorldPosition() };

	// If I am touching a ladder, climb it
	if (auto ladder = IsTouchingLadder())
	{
		// If timer is up, start climbing
		if (m_AccumulatedTime >= m_TimeToClimb)
		{
			// Reset timer
			m_AccumulatedTime = 0;

			// If ladder is above me, speed = -75
			if (ladder->GetTransform().GetWorldPosition().y < enemyPos.y)
			{
				m_Speed = -abs(m_Speed);
			}
			else
			{
				m_Speed = abs(m_Speed);
			}

			// Start climbing
			dae::ClimbStartCommand climbStartCommand{ GetEnemy(), ladder, m_Speed };
			climbStartCommand.Execute(elapsedSec);

			return;
		}
	}

	// Continue moving
	dae::WalkCommand moveCommand{ GetEnemy(), m_Speed };
	moveCommand.Execute(elapsedSec);
}

void dae::WalkingEnemyState::Render(float) const
{
}

void dae::WalkingEnemyState::OnEnter()
{
}

void dae::WalkingEnemyState::OnExit()
{
}

dae::GameObject* dae::WalkingEnemyState::IsTouchingLadder()
{
	// Check if I am touching a ladder
	const auto pEnemy{ GetEnemy() };
	const auto enemyPos{ pEnemy->GetTransform().GetWorldPosition() };
	const auto enemySize{ pEnemy->GetTransform().GetDimensions() };
	
	// For every ladder
	for (auto ladder : dae::SceneManager::GetInstance().GetActiveScene().GetObjectsByTag("Ladder"))
	{
		const auto ladderPos{ ladder->GetTransform().GetWorldPosition() };
		const auto ladderSize{ ladder->GetTransform().GetDimensions() };

		// Check if enemy center x is touching the ladder
		if (enemyPos.x + (enemySize.x / 2) > ladderPos.x &&
			enemyPos.x + (enemySize.x / 2) < ladderPos.x + ladderSize.x)
		{
			// Check if enemy bottom is touching the ladder
			if (enemyPos.y + enemySize.y <= ladderPos.y + ladderSize.y &&
				enemyPos.y + enemySize.y >= ladderPos.y)
			{
				// Get nearest player on y-axis
				auto players = dae::SceneManager::GetInstance().GetActiveScene().GetObjectsByTag("Player");
				auto nearestPlayer{ players.front()};

				for (auto player : players)
				{
					// If player is closer the current nearest player
					if (abs(player->GetTransform().GetWorldPosition().y - enemyPos.y) <
						abs(nearestPlayer->GetTransform().GetWorldPosition().y - enemyPos.y))
					{
						nearestPlayer = player;
					}
				}

				// If nearest player is above me, and ladder is above me, return ladder
				// If nearest player is below me, and ladder is below me, return ladder
				// If ladder is on same level as player, return ladder
				if (nearestPlayer->GetTransform().GetWorldPosition().y <= enemyPos.y && ladderPos.y <= enemyPos.y)
				{
					return ladder;
				}
				else if (nearestPlayer->GetTransform().GetWorldPosition().y >= enemyPos.y && ladderPos.y >= enemyPos.y)
				{
					return ladder;
				}
			}
		}
	}

	// If no ladder is touching enemy, return nullptr
	return nullptr;
}
