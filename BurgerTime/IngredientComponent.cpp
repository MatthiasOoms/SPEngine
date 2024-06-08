#include "PlatformComponent.h"
#include "EnemyComponent.h"
#include "IngredientComponent.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "GameCommands.h"
#include "FallingEnemyState.h"

dae::IngredientComponent::IngredientComponent(GameObject* pOwner, float speed)
	: UpdateComponent(pOwner)
	, m_Type{ "" }
	, m_Id{ 0 }
	, m_IsPressed{ false }
	, m_FloorsToFall{ false }
	, m_FallSpeed{ speed }
{
	RegisterObjects();
}

dae::IngredientComponent::IngredientComponent(GameObject* pOwner)
	: UpdateComponent(pOwner)
	, m_Type{ "" }
	, m_Id{ 0 }
	, m_IsPressed{ false }
	, m_FloorsToFall{ false }
	, m_FallSpeed{ 75.f }
{
	RegisterObjects();
}

void dae::IngredientComponent::Update(float elapsedSec)
{
	if (m_FloorsToFall == -1)
	{
		return;
	}

	// If not pressed and not falling
	if (!m_IsPressed && m_FloorsToFall == 0)
	{
		// Should I be pressed
		HandlePress();
		// Should I be falling
		HandleFall();
	}
	else if (m_FloorsToFall > 0)
	{
		// Fall
		ExecuteFall(elapsedSec);
	}

	// Go over all ingredients
	for (auto ingredient : m_pIngredients)
	{
		// If type is the same
		auto ingredientComp = ingredient->GetComponent<IngredientComponent>();
		if (ingredientComp->GetType() == GetType())
		{
			// If ID is not the same
			if (ingredientComp->GetId() != GetId())
			{
				HandleIngredient(ingredient);
			}
		}
		else
		{
			HandleIngredient(ingredient);
		}
	}
}

void dae::IngredientComponent::HandleFall()
{
	bool fall = true;

	for (auto ingredient : m_pFullIngredient)
	{
		auto ingredientComp = ingredient->GetComponent<IngredientComponent>();

		// If not all segments are pressed, do not fall
		if (!ingredientComp->GetPressed())
		{
			fall = false;
		}
	}

	// If all segments are pressed, fall
	if (fall)
	{
		// Set full ingredient to falling
		for (auto ingredient : m_pFullIngredient)
		{
			ingredient->GetComponent<IngredientComponent>()->IncrementFloorsToFall();
		}
		
		// If an enemy is touching any segment, make all segments fall an extra floor
		for (auto enemy : m_pEnemies)
		{
			auto enemyPos = enemy->GetTransform().GetWorldPosition();
			auto enemyDims = enemy->GetTransform().GetDimensions();

			for (auto ingredient : m_pFullIngredient)
			{
				auto ingredientPos = ingredient->GetTransform().GetWorldPosition();
				auto ingredientDims = ingredient->GetTransform().GetDimensions();

				// If left side of enemy is between left and right side of ingredient
				// or right side of enemy is between left and right side of ingredient
				if (enemyPos.x >= ingredientPos.x && enemyPos.x <= ingredientPos.x + ingredientDims.x ||
					enemyPos.x + enemyDims.x >= ingredientPos.x && enemyPos.x + enemyDims.x <= ingredientPos.x + ingredientDims.x)
				{
					// If top side of enemy is between top and bottom side of ingredient
					// or bottom side of enemy is between top and bottom side of ingredient
					if (enemyPos.y >= ingredientPos.y && enemyPos.y <= ingredientPos.y + ingredientDims.y ||
						enemyPos.y + enemyDims.y >= ingredientPos.y && enemyPos.y + enemyDims.y <= ingredientPos.y + ingredientDims.y)
					{
						// Increment floors to fall
						for (auto ingredientSegment : m_pFullIngredient)
						{
							ingredientSegment->GetComponent<IngredientComponent>()->IncrementFloorsToFall();
						}

						auto enemyComp = enemy->GetComponent<EnemyComponent>();
						enemyComp->SetState(new FallingEnemyState{ enemy, m_FallSpeed });
						dynamic_cast<FallingEnemyState*>(enemyComp->GetCurrentState())->SetFloorsToFall(m_FloorsToFall);
						continue;
					}
				}
			}
		}
	}
}

void dae::IngredientComponent::HandlePress()
{
	auto selfPos = GetOwner()->GetTransform().GetWorldPosition();
	auto selfDims = GetOwner()->GetTransform().GetDimensions();

	// Get all players
	for (auto player : m_pPlayers)
	{
		auto playerPos = player->GetTransform().GetWorldPosition();
		auto playerDims = player->GetTransform().GetDimensions();

		// If left side of self is between left and right side of player
		// or right side of self is between left and right side of player
		if (selfPos.x >= playerPos.x && selfPos.x <= playerPos.x + playerDims.x ||
			selfPos.x + selfDims.x >= playerPos.x && selfPos.x + selfDims.x <= playerPos.x + playerDims.x)
		{
			// If top side of self is between top and bottom side of player
			// or bottom side of self is between top and bottom side of player
			if (selfPos.y >= playerPos.y && selfPos.y <= playerPos.y + playerDims.y ||
				selfPos.y + selfDims.y >= playerPos.y && selfPos.y + selfDims.y <= playerPos.y + playerDims.y)
			{
				// Pressed
				m_IsPressed = true;

				// Move down 2 pixels
				auto& transform = GetOwner()->GetTransform();
				auto local = transform.GetLocalPosition();
				transform.SetLocalPosition(local.x, local.y + 4, local.z);
			}
		}
	}
}

void dae::IngredientComponent::ExecuteFall(float elapsedSec)
{
	// If an enemy is touching any segment, make all segments fall an extra floor
	for (auto enemy : m_pEnemies)
	{
		auto enemyPos = enemy->GetTransform().GetWorldPosition();
		auto enemyDims = enemy->GetTransform().GetDimensions();

		auto ingredientPos = GetOwner()->GetTransform().GetWorldPosition();
		auto ingredientDims = GetOwner()->GetTransform().GetDimensions();

		// If left side of enemy is between left and right side of ingredient
		// or right side of enemy is between left and right side of ingredient
		if (enemyPos.x >= ingredientPos.x && enemyPos.x <= ingredientPos.x + ingredientDims.x ||
			enemyPos.x + enemyDims.x >= ingredientPos.x && enemyPos.x + enemyDims.x <= ingredientPos.x + ingredientDims.x)
		{
			// If top side of enemy is between top and bottom side of ingredient
			// or bottom side of enemy is between top and bottom side of ingredient
			if (enemyPos.y >= ingredientPos.y + (ingredientDims.y / 2) && enemyPos.y <= ingredientPos.y + ingredientDims.y ||
				enemyPos.y + enemyDims.y >= ingredientPos.y + (ingredientDims.y / 2) && enemyPos.y + enemyDims.y <= ingredientPos.y + ingredientDims.y)
			{
				enemy->GetComponent<EnemyComponent>()->Respawn();;
				continue;
			}
		}
	}

	// Move command down
	dae::FallCommand command{ GetOwner(), m_FallSpeed };
	command.Execute(elapsedSec);
}

void dae::IngredientComponent::HandleIngredient(GameObject* pOther)
{
	// If type and ID are not the same
	if (pOther->GetComponent<IngredientComponent>()->GetType() != GetType())
	{
		if (pOther->GetComponent<IngredientComponent>()->GetId() != GetId())
		{
			return;
		}
	}
	

	// This is a fully different Ingredient
	auto selfPos = GetOwner()->GetTransform().GetWorldPosition();
	auto selfDims = GetOwner()->GetTransform().GetDimensions();

	auto ingredientPos = pOther->GetTransform().GetWorldPosition();
	auto ingredientDims = pOther->GetTransform().GetDimensions();

	// If left side of self is between left and right side of ingredient
	// or right side of self is between left and right side of ingredient
	if (selfPos.x >= ingredientPos.x && selfPos.x <= ingredientPos.x + ingredientDims.x ||
		selfPos.x + selfDims.x >= ingredientPos.x && selfPos.x + selfDims.x <= ingredientPos.x + ingredientDims.x)
	{
		// If top side of self is between top and bottom side of ingredient
		// or bottom side of self is between top and bottom side of ingredient
		if (selfPos.y >= ingredientPos.y && selfPos.y <= ingredientPos.y + ingredientDims.y ||
			selfPos.y + selfDims.y >= ingredientPos.y && selfPos.y + selfDims.y <= ingredientPos.y + ingredientDims.y)
		{
			// Two ingredients are colliding
			// If this ingredient is falling, and the other one is not falling
			if (m_FloorsToFall >= 0 && pOther->GetComponent<IngredientComponent>()->GetFalling() <= 0)
			{
				// If other has -1 floors to fall, it is on a plate, so set own floors to fall to -1 and stack on top
				if (pOther->GetComponent<IngredientComponent>()->GetFalling() == -1)
				{
					m_FloorsToFall = -1;

					// Stack self on top of other
					GetOwner()->GetTransform().SetLocalPosition(selfPos.x, ingredientPos.y - selfDims.y, selfPos.z);

					if (m_Type == "BunTop")
					{
						// Inform observer that burger is complete

					}
				}
				else
				{
					// Move the other ingredient down
					pOther->GetComponent<IngredientComponent>()->IncrementFloorsToFall();
				}
			}
		}
	}
}

void dae::IngredientComponent::RegisterObjects()
{
	m_pIngredients = dae::SceneManager::GetInstance().GetActiveScene().GetObjectsByTag("Ingredient");
	m_pEnemies = dae::SceneManager::GetInstance().GetActiveScene().GetObjectsByTag("Enemy");
	m_pPlayers = dae::SceneManager::GetInstance().GetActiveScene().GetObjectsByTag("Player");

	// Get all ingredients
	for (auto ingredient : m_pIngredients)
	{
		// If type is the same
		auto ingredientComp = ingredient->GetComponent<IngredientComponent>();
		if (ingredientComp->GetType() == GetType())
		{
			// If ID is the same
			if (ingredientComp->GetId() == GetId())
			{
				// Add to list
				m_pFullIngredient.push_back(ingredient);
			}
		}
	}
}

void dae::IngredientComponent::RegisterObjects(std::string sceneName)
{
	m_pIngredients = dae::SceneManager::GetInstance().GetScene(sceneName).GetObjectsByTag("Ingredient");
	m_pEnemies = dae::SceneManager::GetInstance().GetScene(sceneName).GetObjectsByTag("Enemy");
	m_pPlayers = dae::SceneManager::GetInstance().GetScene(sceneName).GetObjectsByTag("Player");

	// Get all ingredients
	for (auto ingredient : m_pIngredients)
	{
		// If type is the same
		auto ingredientComp = ingredient->GetComponent<IngredientComponent>();
		if (ingredientComp->GetType() == GetType())
		{
			// If ID is the same
			if (ingredientComp->GetId() == GetId())
			{
				// Add to list
				m_pFullIngredient.push_back(ingredient);
			}
		}
	}
}