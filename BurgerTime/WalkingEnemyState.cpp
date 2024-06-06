#include "WalkingEnemyState.h"
#include "GameCommands.h"
#include "GameObject.h"
#include <SceneManager.h>
#include <Scene.h>
#include "ClimbEnemyState.h"
#include <stdexcept>

dae::WalkingEnemyState::WalkingEnemyState(GameObject* pPlayer)
	: EnemyState(pPlayer)
	, m_Speed{ 75 }
{
}

void dae::WalkingEnemyState::Update(float elapsedSec)
{
	// Find closest player
	GameObject* pClosestPlayer{ dae::SceneManager::GetInstance().GetActiveScene().GetObjectsByTag("Player").front() };
	for (auto player : dae::SceneManager::GetInstance().GetActiveScene().GetObjectsByTag("Player"))
	{
		// Calculate distance to player
		const auto playerPos{ pClosestPlayer->GetTransform().GetWorldPosition() };
		const auto newPlayerPos{ player->GetTransform().GetWorldPosition() };
		const auto distanceToPlayer{ (playerPos - GetEnemy()->GetTransform().GetWorldPosition()) };
		const auto newDistanceToPlayer{ (newPlayerPos - GetEnemy()->GetTransform().GetWorldPosition()) };

		// Save closest player
		if (glm::length(newDistanceToPlayer) < glm::length(distanceToPlayer))
		{
			pClosestPlayer = player;
		}
	}

	// Move towards nearest player ( speed = 75 if right, -75 if left)
	const auto playerPos{ pClosestPlayer->GetTransform().GetWorldPosition() };
	const auto enemyPos{ GetEnemy()->GetTransform().GetWorldPosition() };
	const auto direction{ playerPos - enemyPos };

	// Set speed
	float speed{};
	if (direction.x > 0)
	{
		speed = 75.f;
	}
	else
	{
		speed = -75.f;
	}

	// If speed changed, update speed
	if (m_Speed != speed)
	{
		// Start moving
		m_Speed = speed;
		dae::WalkStartCommand moveStartCommand{ GetEnemy(), m_Speed };
		moveStartCommand.Execute(elapsedSec);
	}
	else
	{
		// Continue moving
		dae::WalkCommand moveCommand{ GetEnemy(), m_Speed };
		moveCommand.Execute(elapsedSec);
	}

	// If I am touching a ladder, climb it
	if (auto ladder = IsTouchingLadder())
	{
		// Make ClimbStartCommand
		// If ladder is above me, speed = -75
		if (ladder->GetTransform().GetWorldPosition().y > enemyPos.y)
		{
			m_Speed = -abs(m_Speed);
		}
		else
		{
			m_Speed = abs(m_Speed);
		}

		dae::ClimbStartCommand climbStartCommand{ GetEnemy(), m_Speed };
		climbStartCommand.Execute(elapsedSec);
	}
}

void dae::WalkingEnemyState::Render(float)
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
				return ladder;
			}
			
		}
	}
	// If no ladder is touching enemy, return 0
	return nullptr;
}
