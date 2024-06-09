#include "PlayerComponent.h"
#include "IdlePlayerState.h"
#include "PlayerState.h"
#include "GameObject.h"
#include "Scene.h"
#include <TextureComponent.h>
#include <ResourceManager.h>
#include "PepperComponent.h"
#include "SceneManager.h"
#include "LivesComponent.h"
#include "EnemyComponent.h"

dae::PlayerComponent::PlayerComponent(GameObject* pOwner)
	: Component(pOwner)
	, m_pCurrentState{ new IdlePlayerState{ pOwner } }
	, m_PepperCount{ 5 }
	, m_PepperCooldown{ 1.0f }
	, m_AccumulatedPepperTime{ 0.0f }
	, m_HurtCooldown{ 3.0f }
	, m_AccumulatedHurtTime{ 0.0f }
{
	RegisterObjects();
}

dae::PlayerComponent::~PlayerComponent()
{
	delete m_pCurrentState;
	m_pCurrentState = nullptr;
}

void dae::PlayerComponent::Update(float elapsedSec)
{
	if (m_AccumulatedPepperTime < m_PepperCooldown)
	{
		m_AccumulatedPepperTime += elapsedSec;
	}

	// Update the current state
	m_pCurrentState->Update(elapsedSec);

	// Check if player is hurt
	if (m_AccumulatedHurtTime < m_HurtCooldown)
	{
		m_AccumulatedHurtTime += elapsedSec;
	}
	else
	{
		auto selfPos = GetOwner()->GetTransform().GetWorldPosition();
		auto selfDims = GetOwner()->GetTransform().GetDimensions();

		// For every enemy
		for (auto pEnemy : m_pEnemies)
		{
			if (!pEnemy->GetComponent<EnemyComponent>()->IsStunned())
			{
				auto enemyPos = pEnemy->GetTransform().GetWorldPosition();
				auto enemyDims = GetOwner()->GetTransform().GetDimensions();

				// Check if player is colliding with enemy
				if (selfPos.x < enemyPos.x + enemyDims.x &&
					selfPos.x + selfDims.x > enemyPos.x &&
					selfPos.y < enemyPos.y + enemyDims.y &&
					selfPos.y + selfDims.y > enemyPos.y)
				{
					// Player is hurt
					m_AccumulatedHurtTime = 0.0f;
					GetOwner()->GetComponent<LivesComponent>()->LowerLives();
					break;
				}
			}
		}
	}
}

void dae::PlayerComponent::Render(float elapsedSec) const
{
	m_pCurrentState->Render(elapsedSec);
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

void dae::PlayerComponent::ThrowPepper()
{
	if (m_PepperCount > 0 && m_AccumulatedPepperTime >= m_PepperCooldown)
	{
		--m_PepperCount;
		m_AccumulatedPepperTime = 0.0f;

		// Get playercomponent
		auto playerTexture = GetOwner()->GetComponent<TextureComponent>();
		auto playerPos = GetOwner()->GetTransform().GetWorldPosition();

		// Make object in direction player is facing
		auto pPepper = std::make_unique<GameObject>("Pepper");
		pPepper->AddComponent<PepperComponent>();
		auto pTexture = pPepper->AddComponent<TextureComponent>();
		pTexture->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Misc/Pepper.png"));
		pTexture->SetScale(2);

		if (playerTexture->GetScale() > 0)
		{
			// Create pepper object on the right side of the player
			auto temp = glm::vec3{ playerTexture->GetDimensions().x, 0, 0 };
			pPepper->SetLocalPosition(glm::vec3{ playerPos + temp });
		}
		else
		{
			// Create pepper object on the left side of the player
			auto temp = glm::vec3{ -pTexture->GetDimensions().x, 0, 0 };
			pPepper->SetLocalPosition(glm::vec3{ playerPos + temp });
		}

		dae::SceneManager::GetInstance().GetActiveScene().Add(std::move(pPepper));
	}
}

void dae::PlayerComponent::RegisterObjects()
{
	m_pEnemies = dae::SceneManager::GetInstance().GetActiveScene().GetObjectsByTag("Enemy");
}

void dae::PlayerComponent::RegisterObjects(std::string sceneName)
{
	m_pEnemies = dae::SceneManager::GetInstance().GetScene(sceneName).GetObjectsByTag("Enemy");
}
