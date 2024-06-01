#include "CollisionComponent.h"
#include "PlatformComponent.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Scene.h"

dae::PlatformComponent::PlatformComponent(GameObject* pOwner)
	: UpdateComponent(pOwner)
{
	RegisterObjects();
}

void dae::PlatformComponent::Update(float)
{
	// Get the object's position and dimensions
	auto objPos = GetOwner()->GetTransform().GetWorldPosition();
	auto objDims = GetOwner()->GetComponent<CollisionComponent>();
	int objWidth = objDims->GetWidth();
	int objHeight = objDims->GetHeight();

	for (auto pPlayer : m_pPlayers)
	{
		// Get the player's position and dimensions
		auto playerPos = pPlayer->GetTransform().GetWorldPosition();
		auto playerDims = pPlayer->GetComponent<CollisionComponent>();
		int playerWidth = playerDims->GetWidth();
		int playerHeight = playerDims->GetHeight();

		// If player left or right is in the object
		if ((playerPos.x < objPos.x + objWidth && playerPos.x > objPos.x) 
			|| (playerPos.x + playerWidth < objPos.x + objWidth && playerPos.x + playerWidth > objPos.x))
		{
			// If player bottom is in the object
			if (playerPos.y + playerHeight > objPos.y && playerPos.y < objPos.y)
			{
				// Move up
				pPlayer->SetLocalPosition(glm::vec3{ playerPos.x, objPos.y - playerHeight, playerPos.z });
			}
			// If player top is in the object
			else if (playerPos.y < objPos.y + objHeight && playerPos.y > objPos.y + objHeight - playerHeight)
			{
				// Move down
				pPlayer->SetLocalPosition(glm::vec3{ playerPos.x, objPos.y + objHeight, playerPos.z });
			}
		}
	}
}

void dae::PlatformComponent::RegisterObjects()
{
	// Get all players, enemies and ingredients
	auto temp = dae::SceneManager::GetInstance().GetActiveScene();
	m_pPlayers = temp->GetObjectsByTag("Player");
	m_pEnemies = temp->GetObjectsByTag("Enemy");
	m_pIngredients = temp->GetObjectsByTag("Ingredient");

	// Add collision components to all players, enemies and ingredients if necessary
	for (auto pPlayer : m_pPlayers)
	{
		if (!pPlayer->HasComponent<CollisionComponent>())
		{
			pPlayer->AddComponent<CollisionComponent>();
		}
	}

	for (auto pEnemy : m_pEnemies)
	{
		if (!pEnemy->HasComponent<CollisionComponent>())
		{
			pEnemy->AddComponent<CollisionComponent>();
		}
	}

	for (auto pIngredient : m_pIngredients)
	{
		if (!pIngredient->HasComponent<CollisionComponent>())
		{
			pIngredient->AddComponent<CollisionComponent>();
		}
	}
}

void dae::PlatformComponent::RegisterObjects(std::string scene)
{
	// Get all players, enemies and ingredients
	if (auto temp = dae::SceneManager::GetInstance().GetScene(scene))
	{
		m_pPlayers = temp->GetObjectsByTag("Player");
		m_pEnemies = temp->GetObjectsByTag("Enemy");
		m_pIngredients = temp->GetObjectsByTag("Ingredient");

		// Add collision components to all players, enemies and ingredients if necessary
		for (auto pPlayer : m_pPlayers)
		{
			if (!pPlayer->HasComponent<CollisionComponent>())
			{
				pPlayer->AddComponent<CollisionComponent>();
			}
		}

		for (auto pEnemy : m_pEnemies)
		{
			if (!pEnemy->HasComponent<CollisionComponent>())
			{
				pEnemy->AddComponent<CollisionComponent>();
			}
		}

		for (auto pIngredient : m_pIngredients)
		{
			if (!pIngredient->HasComponent<CollisionComponent>())
			{
				pIngredient->AddComponent<CollisionComponent>();
			}
		}
	}
	else
	{
		throw std::exception("Scene not found");
	}
}
