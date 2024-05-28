#include "PlayerComponent.h"
#include "IdlePlayerState.h"
#include "PlayerState.h"
#include "GameObject.h"
#include "Scene.h"
#include "CollisionComponent.h"

dae::PlayerComponent::PlayerComponent(GameObject* pOwner)
	: Component(pOwner)
	, m_pCurrentState{ new IdlePlayerState{ pOwner } }
	, m_SceneManager{ SceneManager::GetInstance() }
{
	SetStaticLevel();

	m_pPlayer = GetOwner();

	if (!m_pPlayer->HasComponent<CollisionComponent>())
	{
		m_pPlayer->AddComponent<CollisionComponent>();
	}

	m_pPlayerDimensions = m_pPlayer->GetComponent<CollisionComponent>();
}

dae::PlayerComponent::~PlayerComponent()
{
	delete m_pCurrentState;
	m_pCurrentState = nullptr;
}

void dae::PlayerComponent::Update(float elapsedSec)
{
	// Update the current state
	m_pCurrentState->Update(elapsedSec);

	// Get the player's position and dimensions
	auto playerPos = m_pPlayer->GetTransform().GetWorldPosition();
	int playerWidth = m_pPlayerDimensions->GetWidth();
	int playerHeight = m_pPlayerDimensions->GetHeight();

	// Check for collisions with the static level (Platforms)
	for (GameObject* pObject : m_pStaticLevel)
	{
		// Get the object's position and dimensions
		auto objPosition = pObject->GetTransform().GetWorldPosition();
		auto objDimensions = pObject->GetComponent<CollisionComponent>();
		
		// If player left or right is in the object
		if ((playerPos.x < objPosition.x + objDimensions->GetWidth() && playerPos.x > objPosition.x) || (playerPos.x + playerWidth < objPosition.x + objDimensions->GetWidth() && playerPos.x + playerWidth > objPosition.x))
		{
			// If player bottom is in the object
			if (playerPos.y + playerHeight > objPosition.y && playerPos.y < objPosition.y)
			{
				// Move up
				GetOwner()->SetLocalPosition(glm::vec3{ playerPos.x, objPosition.y - playerHeight, playerPos.z });
			}
			// If player top is in the object
			else if (playerPos.y < objPosition.y + objDimensions->GetHeight() && playerPos.y > objPosition.y + objDimensions->GetHeight() - playerHeight)
			{
				// Move down
				GetOwner()->SetLocalPosition(glm::vec3{ playerPos.x, objPosition.y + objDimensions->GetHeight(), playerPos.z });
			}
		}
		
	}
}

void dae::PlayerComponent::Render(float elapsedSec) const
{
	m_pCurrentState->Render(elapsedSec);
}

void dae::PlayerComponent::SetStaticLevel()
{
	auto temp = m_SceneManager.GetActiveScene()->GetObjectsByTag("StaticLevel");
	for (GameObject* pObject : temp)
	{
		if (pObject->HasComponent<CollisionComponent>())
		{
			m_pStaticLevel.push_back(pObject);
		}
	}
}

void dae::PlayerComponent::SetState(PlayerState* pState)
{
	if (pState != nullptr)
	{
		if (m_pCurrentState)
		{
			m_pCurrentState->OnExit();
			delete m_pCurrentState;
		}
		m_pCurrentState = pState;
		m_pCurrentState->OnEnter();
	}
}
