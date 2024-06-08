#ifndef INGREDIENTCOMPONENT_H
#define INGREDIENTCOMPONENT_H
#include <vector>
#include <string>
#include "Component.h"

namespace dae
{
	class GameObject;

	class IngredientComponent : public UpdateComponent
	{
	public:
		IngredientComponent(GameObject* pOwner, float speed);
		IngredientComponent(GameObject* pOwner);
		virtual ~IngredientComponent() = default;

		virtual void Update(float elapsedSec) override;

		void SetType(const std::string& type) { m_Type = type; }
		const std::string& GetType() const { return m_Type; }

		void SetId(int id) { m_Id = id; }
		int GetId() const { return m_Id; }

		void SetPressed(bool pressed) { m_IsPressed = pressed; }
		bool GetPressed() const { return m_IsPressed; }

		void IncrementFloorsToFall() { ++m_FloorsToFall; }
		void DecrementFloorsToFall();
		void SetFloorsToFall(int floors) { m_FloorsToFall = floors; }
		int GetFalling() const { return m_FloorsToFall; }

		void RegisterObjects();
		void RegisterObjects(std::string sceneName);
	private:
		std::string m_Type;
		int m_Id;

		bool m_IsPressed;
		int m_FloorsToFall;
		float m_FallSpeed;

		std::vector<GameObject*> m_pFullIngredient;
		std::vector<GameObject*> m_pIngredients;
		std::vector<GameObject*> m_pEnemies;
		std::vector<GameObject*> m_pPlayers;

		void HandleFall();
		void HandlePress();
		void ExecuteFall(float elapsedSec);
		void HandleIngredient(GameObject* pOther);
	};
}

#endif // ! INGREDIENTCOMPONENT_H
