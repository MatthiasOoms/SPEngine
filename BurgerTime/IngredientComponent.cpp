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
	, m_IsFalling(false)
{
}

void dae::IngredientComponent::Update(float elapsedSec)
{
	if (!m_IsPressed && !m_IsFalling)
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

		if (fall)
		{
			for (auto ingredientSegment : fullIngredient)
			{
				ingredientSegment->GetComponent<IngredientComponent>()->SetFalling(true);
			}
		}
	}
	else if (m_IsFalling)
	{
		HandleFall(elapsedSec);
	}
}

void dae::IngredientComponent::Reset()
{
	m_IsPressed = false;
	m_IsFalling = false;
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
