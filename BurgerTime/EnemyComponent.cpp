#include "EnemyComponent.h"
#include "WalkingEnemyState.h"
#include "EnemyState.h"
#include "GameObject.h"
#include <TextureComponent.h>
#include <ResourceManager.h>
#include "FallingEnemyState.h"
#include "Subject.h"
#include "Observer.h"
#include "ScoreComponent.h"
#include <SceneManager.h>
#include <Scene.h>

dae::EnemyComponent::EnemyComponent(GameObject* pOwner)
	: Component(pOwner)
	, m_pCurrentState{ new WalkingEnemyState{ pOwner } }
	, m_Type{ EnemyType::Hotdog }
	, m_IsStunned{ false }
	, m_StunDuration{ 1.5f }
	, m_AccumulatedPepperTime{ 0.0f }
	, m_pPreStunTexture{ nullptr }
	, m_pSubject{ new Subject{} }
	, m_IsControlled{ false }
{
	m_pHotdogStunned = dae::ResourceManager::GetInstance().LoadTexture("HotdogStunned.png");
	m_pEggStunned = dae::ResourceManager::GetInstance().LoadTexture("EggStunned.png");
	m_pPickleStunned = dae::ResourceManager::GetInstance().LoadTexture("PickleStunned.png");
}

dae::EnemyComponent::~EnemyComponent()
{
	if (m_pCurrentState)
	{
		delete m_pCurrentState;
		m_pCurrentState = nullptr;
	}

	delete m_pSubject;
	m_pSubject = nullptr;
}

void dae::EnemyComponent::Update(float elapsedSec)
{
	if (m_pCurrentState)
	{
		// If falling or not stunned
		if (!m_IsStunned || dynamic_cast<FallingEnemyState*>(m_pCurrentState))
		{
			// Update the current state
			m_pCurrentState->Update(elapsedSec);
		}
		else
		{
			m_AccumulatedPepperTime += elapsedSec;
			if (m_AccumulatedPepperTime >= m_StunDuration)
			{
				m_IsStunned = false;
				m_AccumulatedPepperTime = 0.0f;

				// Set Texture back to normal
				GetOwner()->GetComponent<TextureComponent>()->SetTexture(m_pPreStunTexture);
			}
		}
	}
}

void dae::EnemyComponent::Render(float elapsedSec) const
{
	if (m_pCurrentState)
	{
		if (!m_IsStunned)
		{
			m_pCurrentState->Render(elapsedSec);
		}
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
	else
	{
		if (m_pCurrentState)
		{
			m_pCurrentState->OnExit();
			delete m_pCurrentState;
		}
		m_pCurrentState = pState;
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
		pTextureComp->SetTexture(m_pHotdogStunned);
		break;
	case EnemyType::Egg:
		pTextureComp->SetTexture(m_pEggStunned);
		break;
	case EnemyType::Pickle:
		pTextureComp->SetTexture(m_pPickleStunned);
		break;
	default:
		break;
	}
}

void dae::EnemyComponent::Respawn()
{
	// Move to left or right of screen depending on distance from center
	auto pos = GetOwner()->GetTransform().GetLocalPosition();
	auto dims = GetOwner()->GetTransform().GetDimensions();

	if (pos.x > 240)
	{
		GetOwner()->GetTransform().SetLocalPosition(480.f - 32.f - dims.x, pos.y, pos.z);
	}
	else
	{
		GetOwner()->GetTransform().SetLocalPosition(32, pos.y, pos.z);
	}

	// Stun Enemy
	Stun();

	// Get Player 1 score component
	auto pScoreComp = dae::SceneManager::GetInstance().GetActiveScene().GetObjectsByTag("Player").front()->GetComponent<ScoreComponent>();

	switch (m_Type)
	{
	case dae::EnemyType::Hotdog:
		pScoreComp->HotdogDeath();
		break;
	case dae::EnemyType::Egg:
		pScoreComp->EggDeath();
		break;
	case dae::EnemyType::Pickle:
		pScoreComp->PickleDeath();
		break;
	default:
		break;
	}
}

void dae::EnemyComponent::AddObserver(Observer* pObserver)
{
	m_pSubject->AddObserver(pObserver);
	pObserver->OnNotify(GetOwner(), Event::ObserverAdded);
}