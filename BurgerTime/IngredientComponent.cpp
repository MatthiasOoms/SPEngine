#include "IngredientComponent.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "GameCommands.h"

dae::IngredientComponent::IngredientComponent(GameObject* pOwner)
	: UpdateComponent(pOwner)
	, m_Type("")
	, m_Id(0)
	, m_IsPressed(false)
	, m_LayersToFall(false)
{
}

void dae::IngredientComponent::Update(float elapsedSec)
{
	if (!m_IsPressed && !m_LayersToFall)
	{
		HandlePress();
		
		bool fall = true;
		std::vector<GameObject*> fullIngredient;

		// Get all ingredients
		for (auto ingredient : dae::SceneManager::GetInstance().GetActiveScene().GetObjectsByTag("Ingredient"))
		{
			// If type is the same
			auto ingredientComp = ingredient->GetComponent<IngredientComponent>();
			if (ingredientComp->GetType() == GetType())
			{
				// If ID is the same
				if (ingredientComp->GetId() == GetId())
				{
					// Add to list
					fullIngredient.push_back(ingredient);

					// We belong to the same Ingredient whole
					if (!ingredientComp->GetPressed())
					{
						fall = false;
					}
				}
			}
		}

		// If all segments are pressed, fall
		if (fall)
		{
			int enemiesOverlapping{};

			// For every enemy
			for (auto enemy : dae::SceneManager::GetInstance().GetActiveScene().GetObjectsByTag("Enemy"))
			{
				// For every segment
				for (auto ingredientSegment : fullIngredient)
				{
					// If the enemy touches any of the segments, it will fall an extra layer
					// It will not check the other segments
					auto enemyPos = enemy->GetTransform().GetWorldPosition();
					auto enemyDims = enemy->GetTransform().GetDimensions();

					auto ingredientPos = ingredientSegment->GetTransform().GetWorldPosition();
					auto ingredientDims = ingredientSegment->GetTransform().GetDimensions();

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
							// Fall
							++enemiesOverlapping;
							break;
						}
					}
				}
			}
			// For every segment
			for (auto ingredientSegment : fullIngredient)
			{
				// For the amount of enemies touching the full ingredient, fall an extra layer
				for (int i{}; i <= enemiesOverlapping; ++i)
				{
					ingredientSegment->GetComponent<IngredientComponent>()->FallingLayersIncrement();
				}
			}
			
		}
	}
	else if (m_LayersToFall > 0)
	{
		HandleFall(elapsedSec);
	}

	// Go over all ingredients
	for (auto ingredient : dae::SceneManager::GetInstance().GetActiveScene().GetObjectsByTag("Ingredient"))
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

void dae::IngredientComponent::HandlePress()
{
	auto selfPos = GetOwner()->GetTransform().GetWorldPosition();
	auto selfDims = GetOwner()->GetTransform().GetDimensions();

	// Get all players
	for (auto player : dae::SceneManager::GetInstance().GetActiveScene().GetObjectsByTag("Player"))
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

void dae::IngredientComponent::HandleFall(float elapsedSec)
{
	// Move command down
	dae::FallCommand command{ GetOwner(), 75 };
	command.Execute(elapsedSec);
}

void dae::IngredientComponent::HandleIngredient(GameObject* pOther)
{
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
			pOther->GetComponent<IngredientComponent>()->HandlePress();
			pOther->GetComponent<IngredientComponent>()->FallingLayersIncrement();
		}
	}
}
