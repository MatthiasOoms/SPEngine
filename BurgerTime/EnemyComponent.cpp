#include "EnemyComponent.h"
#include "WalkingEnemyState.h"
#include "EnemyState.h"
#include "GameObject.h"
#include <TextureComponent.h>
#include <ResourceManager.h>
#include "FallingEnemyState.h"

dae::EnemyComponent::EnemyComponent(GameObject* pOwner)
	: Component(pOwner)
	, m_pCurrentState{ new WalkingEnemyState{ pOwner } }
	, m_Type{ EnemyType::Hotdog }
	, m_IsStunned{ false }
	, m_StunDuration{ 1.5f }
	, m_AccumulatedTime{ 0.0f }
	, m_pPreStunTexture{ nullptr }
{
}

dae::EnemyComponent::~EnemyComponent()
{
	delete m_pCurrentState;
	m_pCurrentState = nullptr;
}

void dae::EnemyComponent::Update(float elapsedSec)
{
	// If falling or not stunned
	if (!m_IsStunned || dynamic_cast<FallingEnemyState*>(m_pCurrentState))
	{
		// Update the current state
		m_pCurrentState->Update(elapsedSec);
	}
	else
	{
		m_AccumulatedTime += elapsedSec;
		if (m_AccumulatedTime >= m_StunDuration)
		{
			m_IsStunned = false;
			m_AccumulatedTime = 0.0f;

			// Set Texture back to normal
			GetOwner()->GetComponent<TextureComponent>()->SetTexture(m_pPreStunTexture);

		}
	}
}

void dae::EnemyComponent::Render(float elapsedSec) const
{
	if (!m_IsStunned)
	{
		m_pCurrentState->Render(elapsedSec);
	}
}

void dae::EnemyComponent::SetState(EnemyState* pState)
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

void dae::EnemyComponent::SetType(EnemyType type)
{
	m_Type = type;
}

void dae::EnemyComponent::Stun()
{
	m_IsStunned = true;

	m_pPreStunTexture = GetOwner()->GetComponent<TextureComponent>()->GetTexture();

	// Set Texture to stunned texture
	auto pTextureComp = GetOwner()->GetComponent<TextureComponent>();

	switch (m_Type)
	{
	case EnemyType::Hotdog:
		pTextureComp->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("HotdogStunned.png"));
		break;
	case EnemyType::Egg:
		pTextureComp->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("EggStunned.png"));
		break;
	case EnemyType::Pickle:
		pTextureComp->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("PickleStunned.png"));
		break;
	default:
		break;
	}
}
