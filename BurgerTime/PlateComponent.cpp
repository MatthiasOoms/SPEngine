#include "PlateComponent.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "IngredientComponent.h"

dae::PlateComponent::PlateComponent(GameObject* pOwner)
	: UpdateComponent(pOwner)
{
}

void dae::PlateComponent::Update(float)
{
	auto selfPos = GetOwner()->GetTransform().GetLocalPosition();
	auto selfDims = GetOwner()->GetTransform().GetDimensions();

	// Get all ingredients
	for (auto ingredient : dae::SceneManager::GetInstance().GetActiveScene().GetObjectsByTag("Ingredient"))
	{
		auto ingredientPos = ingredient->GetTransform().GetLocalPosition();
		auto ingredientDims = ingredient->GetTransform().GetDimensions();

		// If left side of self is between left and right side of ingredient
		// or right side of self is between left and right side of ingredient
		if (ingredientPos.x >= selfPos.x && ingredientPos.x <= selfPos.x + selfDims.x ||
			ingredientPos.x + ingredientDims.x >= selfPos.x && ingredientPos.x + ingredientDims.x <= selfPos.x + selfDims.x)
		{
			// If top side of self is between top and bottom side of ingredient
			// or bottom side of self is between top and bottom side of ingredient
			if (ingredientPos.y >= selfPos.y && ingredientPos.y <= selfPos.y + selfDims.y ||
				ingredientPos.y + ingredientDims.y >= selfPos.y && ingredientPos.y + ingredientDims.y <= selfPos.y + selfDims.y)
			{
				ingredient->GetTransform().SetLocalPosition(ingredientPos.x, selfPos.y + selfDims.y - 2 - ingredientDims.y, ingredientPos.z);
				ingredient->GetComponent<IngredientComponent>()->SetFloorsToFall(-1);
			}
		}
	}
}
