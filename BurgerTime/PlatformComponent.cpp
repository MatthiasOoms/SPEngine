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
	auto objDims = GetOwner()->GetTransform().GetDimensions();
	int objWidth = objDims.x;
	int objHeight = objDims.y;

	for (auto pPlayer : m_pPlayers)
	{
		// Get the player's position and dimensions
		auto playerPos = pPlayer->GetTransform().GetWorldPosition();
		auto playerDims = pPlayer->GetTransform().GetDimensions();
		int playerWidth = playerDims.x;
		int playerHeight = playerDims.y;

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
}

void dae::PlatformComponent::RegisterObjects(std::string scene)
{
	// Get all players, enemies and ingredients
	if (auto temp = dae::SceneManager::GetInstance().GetScene(scene))
	{
		m_pPlayers = temp->GetObjectsByTag("Player");
		m_pEnemies = temp->GetObjectsByTag("Enemy");
		m_pIngredients = temp->GetObjectsByTag("Ingredient");
	}
	else
	{
		throw std::exception("Scene not found");
	}
}
