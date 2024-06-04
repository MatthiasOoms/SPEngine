#include "PlatformComponent.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "PlayerComponent.h"
#include "ClimbPlayerState.h"

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

		// Get the player's position and dimensions
		auto playerPos = pPlayer->GetTransform().GetWorldPosition();
		auto playerDims = pPlayer->GetTransform().GetDimensions();
		int playerWidth = playerDims.x;
		int playerHeight = playerDims.y;

		// If player left and right is in the object
		if ((playerPos.x < objPos.x + objWidth && playerPos.x > objPos.x) 
			&& (playerPos.x + playerWidth < objPos.x + objWidth && playerPos.x + playerWidth > objPos.x))
		{
			// If player bottom is in the object
			if (playerPos.y + playerHeight <= objPos.y + objHeight && playerPos.y + playerHeight >= objPos.y)
			{
				// Move up
				pPlayer->SetLocalPosition(glm::vec3{ playerPos.x, objPos.y - playerHeight, playerPos.z });
			}
		}
		// If left or right is not inside
		else if (playerPos.y + playerHeight >= objPos.y && playerPos.y + playerHeight <= objPos.y + objHeight)
		{
			// Move player back inside
			if (playerPos.x <= objPos.x)
			{
				pPlayer->SetLocalPosition(glm::vec3{ objPos.x, playerPos.y, playerPos.z });
			}
			else
			{
				pPlayer->SetLocalPosition(glm::vec3{ objPos.x + objWidth - playerWidth, playerPos.y, playerPos.z });
			}
		}
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
