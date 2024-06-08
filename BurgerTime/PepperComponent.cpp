#include "PepperComponent.h"
#include "GameObject.h"
#include <TextureComponent.h>
#include <ResourceManager.h>
#include <SceneManager.h>
#include <Scene.h>
#include "EnemyComponent.h"


dae::PepperComponent::PepperComponent(GameObject* pOwner)
	: UpdateComponent(pOwner)
	, m_PepperCooldown{ 1.0f }
	, m_AccumulatedTime{ 0.0f }
{
	RegisterObjects();
}

void dae::PepperComponent::Update(float elapsedSec)
{
	if (m_AccumulatedTime < m_PepperCooldown)
	{
		m_AccumulatedTime += elapsedSec;

		auto selfPos = GetOwner()->GetTransform().GetWorldPosition();
		auto selfDims = GetOwner()->GetTransform().GetDimensions();

		for (auto enemy : m_pEnemies)
		{
			auto enemyPos = enemy->GetTransform().GetWorldPosition();
			auto enemyDims = enemy->GetTransform().GetDimensions();

			if (selfPos.x + (selfDims.x / 2) < enemyPos.x + enemyDims.x &&
				selfPos.x + (selfDims.x / 2) > enemyPos.x &&
				selfPos.y < enemyPos.y + enemyDims.y &&
				selfPos.y + selfDims.y > enemyPos.y)
			{
				if (enemy->HasComponent<EnemyComponent>())
				{
					// If not already stunned, stun the enemy
					if (!enemy->GetComponent<EnemyComponent>()->IsStunned())
					{
						enemy->GetComponent<EnemyComponent>()->Stun();
					}
				}
			}
		}
	}
	else
	{
		GetOwner()->Kill();
	}
}

void dae::PepperComponent::RegisterObjects()
{
	m_pEnemies = SceneManager::GetInstance().GetActiveScene().GetObjectsByTag("Enemy");
}

void dae::PepperComponent::RegisterObjects(std::string sceneName)
{
	m_pEnemies = SceneManager::GetInstance().GetScene(sceneName).GetObjectsByTag("Enemy");
}

