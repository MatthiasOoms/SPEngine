#include "PlayerComponent.h"
#include "IdlePlayerState.h"
#include "PlayerState.h"
#include "GameObject.h"
#include "Scene.h"
#include <TextureComponent.h>
#include <ResourceManager.h>
#include "PepperComponent.h"

dae::PlayerComponent::PlayerComponent(GameObject* pOwner)
	: Component(pOwner)
	, m_pCurrentState{ new IdlePlayerState{ pOwner } }
	, m_PepperCount{ 5 }
	, m_PepperCooldown{ 1.0f }
	, m_AccumulatedTime{ 0.0f }
{
}

dae::PlayerComponent::~PlayerComponent()
{
	delete m_pCurrentState;
	m_pCurrentState = nullptr;
}

void dae::PlayerComponent::Update(float elapsedSec)
{
	if (m_AccumulatedTime < m_PepperCooldown)
	{
		m_AccumulatedTime += elapsedSec;
	}

	// Update the current state
	m_pCurrentState->Update(elapsedSec);
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
	if (m_PepperCount > 0 && m_AccumulatedTime >= m_PepperCooldown)
	{
		--m_PepperCount;
		m_AccumulatedTime = 0.0f;

		// Get playercomponent
		auto playerTexture = GetOwner()->GetComponent<TextureComponent>();
		auto playerPos = GetOwner()->GetTransform().GetWorldPosition();

		// Make object in direction player is facing
		auto pPepper = std::make_unique<GameObject>("Pepper");
		pPepper->AddComponent<PepperComponent>();
		auto pTexture = pPepper->AddComponent<TextureComponent>();
		pTexture->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Pepper.png"));
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
