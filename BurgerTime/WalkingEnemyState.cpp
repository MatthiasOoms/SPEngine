#include "WalkingEnemyState.h"
#include "GameCommands.h"
#include "GameObject.h"
#include <SceneManager.h>
#include <Scene.h>

dae::WalkingEnemyState::WalkingEnemyState(GameObject* pPlayer)
	: EnemyState(pPlayer)
	, m_Speed{ 75 }
{
}

void dae::WalkingEnemyState::Update(float elapsedSec)
{
	// Find closest player
	GameObject* pClosestPlayer{ nullptr };
	for (auto player : dae::SceneManager::GetInstance().GetActiveScene().GetObjectsByTag("Player"))
	{
		// Save closest player
		if (pClosestPlayer == nullptr)
		{
			pClosestPlayer = player;
		}
		else
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

		// Move towards player ( speed = 75 if right, -75 if left)
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
		// Update speed
		
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