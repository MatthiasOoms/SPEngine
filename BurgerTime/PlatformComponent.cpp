#include "FallingEnemyState.h"
#include "PlatformComponent.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "PlayerComponent.h"
#include "ClimbPlayerState.h"
#include "EnemyComponent.h"
#include "ClimbEnemyState.h"
#include "IngredientComponent.h"

dae::PlatformComponent::PlatformComponent(GameObject* pOwner)
	: UpdateComponent(pOwner)
	, m_EnemyPassedThrough{ false }
{
	RegisterObjects();
}

void dae::PlatformComponent::Update(float)
{
	// Check if any player is on the platform
	for (auto pPlayer : m_pPlayers)
	{
		if (pPlayer->HasComponent<dae::PlayerComponent>())
		{
			// If the player is climbing, they cannot collide with the platform
			auto playerComp = pPlayer->GetComponent<dae::PlayerComponent>();
			if (dynamic_cast<ClimbPlayerState*>(playerComp->GetCurrentState()))
			{
				continue;
			}
		}

		HandleCollision(pPlayer);
	}

	// Check if any enemy is on the platform
	for (auto pEnemy : m_pEnemies)
	{
		auto enemyFall = dynamic_cast<FallingEnemyState*>(pEnemy->GetComponent<EnemyComponent>()->GetCurrentState());
		// Only check if the enemy is not falling
		if (!enemyFall)
		{
			HandleCollision(pEnemy);
		}
		else
		{
			HandleFallCollision(pEnemy);
		}
	}

	// Check if any ingredient is on the platform
	for (auto pIngredient : m_pIngredients)
	{
		HandleCollision(pIngredient);
	}
}

void dae::PlatformComponent::RegisterObjects()
{
	// Get all players, enemies and ingredients
	auto& scene = dae::SceneManager::GetInstance().GetActiveScene();
	m_pPlayers = scene.GetObjectsByTag("Player");
	m_pEnemies = scene.GetObjectsByTag("Enemy");
	m_pIngredients = scene.GetObjectsByTag("Ingredient");
}

void dae::PlatformComponent::RegisterObjects(std::string scene)
{
	// Get all players, enemies and ingredients
	if (dae::SceneManager::GetInstance().HasScene(scene))
	{
		auto& currentScene = dae::SceneManager::GetInstance().GetScene(scene);
		m_pPlayers = currentScene.GetObjectsByTag("Player");
		m_pEnemies = currentScene.GetObjectsByTag("Enemy");
		m_pIngredients = currentScene.GetObjectsByTag("Ingredient");
	}
	else
	{
		throw std::exception("Scene not found");
	}
}

void dae::PlatformComponent::HandleCollision(GameObject* pCollider)
{
	// Get the object's position and dimensions
	auto objPos = GetOwner()->GetTransform().GetWorldPosition();
	auto objDims = GetOwner()->GetTransform().GetDimensions();
	int objWidth = objDims.x;
	int objHeight = objDims.y;

	// Get the player's position and dimensions
	auto colliderPos = pCollider->GetTransform().GetWorldPosition();
	auto colliderDims = pCollider->GetTransform().GetDimensions();
	int colliderWidth = colliderDims.x;
	int colliderHeight = colliderDims.y;

	// If enemy is climbing down, do not collide
	if (pCollider->HasComponent<EnemyComponent>())
	{
		auto stateComp = pCollider->GetComponent<EnemyComponent>();

		if (auto climbState = dynamic_cast<ClimbEnemyState*>(stateComp->GetCurrentState()))
		{
			if (climbState->GetSpeed() > 0)
			{
				return;
			}
		}
	}

	if (pCollider->HasComponent<IngredientComponent>())
	{
		auto stateComp = pCollider->GetComponent<IngredientComponent>();
		if (stateComp->GetFalling())
		{
			HandleIngredientCollision(pCollider);
		}
		return;
	}

	// If player left and right is in the object
	if ((colliderPos.x <= objPos.x + objWidth && colliderPos.x >= objPos.x)
		&& (colliderPos.x + colliderWidth <= objPos.x + objWidth && colliderPos.x + colliderWidth >= objPos.x))
	{
		// If player bottom is in the object
		if (colliderPos.y + colliderHeight <= objPos.y + objHeight && colliderPos.y + colliderHeight >= objPos.y)
		{
			// Move up
			pCollider->SetLocalPosition(glm::vec3{ colliderPos.x, objPos.y - colliderHeight, colliderPos.z });
		}
	}
	// If player height is in the object
	else if (colliderPos.y + colliderHeight >= objPos.y && colliderPos.y + colliderHeight <= objPos.y + objHeight)
	{
		// If player center is in the object
		if (colliderPos.x + (colliderDims.x / 2) < objPos.x + objDims.x && colliderPos.x + (colliderDims.x / 2) > objPos.x)
		{
			// Move player back inside
			if (colliderPos.x <= objPos.x)
			{
				pCollider->SetLocalPosition(glm::vec3{ objPos.x, colliderPos.y, colliderPos.z });
			}
			else
			{
				pCollider->SetLocalPosition(glm::vec3{ objPos.x + objWidth - colliderWidth, colliderPos.y, colliderPos.z });
			}
		}
	}
}

void dae::PlatformComponent::HandleFallCollision(GameObject* pCollider)
{
	// Get the object's position and dimensions
	auto objPos = GetOwner()->GetTransform().GetWorldPosition();
	auto objDims = GetOwner()->GetTransform().GetDimensions();
	int objWidth = objDims.x;

	// Get the player's position and dimensions
	auto colliderPos = pCollider->GetTransform().GetWorldPosition();
	auto colliderDims = pCollider->GetTransform().GetDimensions();
	int colliderWidth = colliderDims.x;
	int colliderHeight = colliderDims.y;

	// If player left and right is in the object
	if ((colliderPos.x <= objPos.x + objWidth && colliderPos.x >= objPos.x) &&
		(colliderPos.x + colliderWidth <= objPos.x + objWidth && colliderPos.x + colliderWidth >= objPos.x))
	{
		// If player bottom is in the object
		if (colliderPos.y + colliderHeight <= objPos.y + objDims.y && colliderPos.y + colliderHeight >= objPos.y)
		{
			if (m_EnemyPassedThrough)
			{
				return;
			}

			auto enemyComp = pCollider->GetComponent<EnemyComponent>();
			auto enemyFall = dynamic_cast<FallingEnemyState*>(enemyComp->GetCurrentState());
			enemyFall->SetFloorsToFall(enemyFall->GetFloorsToFall() - 1);
			m_EnemyPassedThrough = true;
		}
		else
		{
			m_EnemyPassedThrough = false;
		}
	}
	else
	{
		m_EnemyPassedThrough = false;
	}
}

void dae::PlatformComponent::HandleIngredientCollision(GameObject* pCollider)
{
	// Get the object's position and dimensions
	auto objPos = GetOwner()->GetTransform().GetWorldPosition();
	auto objDims = GetOwner()->GetTransform().GetDimensions();
	int objWidth = objDims.x;

	// Get the player's position and dimensions
	auto colliderPos = pCollider->GetTransform().GetWorldPosition();
	auto colliderDims = pCollider->GetTransform().GetDimensions();
	int colliderWidth = colliderDims.x;
	int colliderHeight = colliderDims.y;

	// If player left and right is in the object
	if ((colliderPos.x <= objPos.x + objWidth && colliderPos.x >= objPos.x) &&
		(colliderPos.x + colliderWidth <= objPos.x + objWidth && colliderPos.x + colliderWidth >= objPos.x))
	{
		// If player bottom is in the object
		if (colliderPos.y + colliderHeight <= objPos.y + objDims.y && colliderPos.y + colliderHeight >= objPos.y)
		{
			// Move up
			pCollider->SetLocalPosition(glm::vec3{ colliderPos.x, objPos.y - colliderHeight + objDims.y, colliderPos.z });
			
			auto ingredientComp = pCollider->GetComponent<IngredientComponent>();
			ingredientComp->DecrementFloorsToFall();
		}
	}
}
