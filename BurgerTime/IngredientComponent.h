#pragma once
#include <vector>
#include <string>
#include "Component.h"

namespace dae
{
	class GameObject;

	class IngredientComponent : public UpdateComponent
	{
	public:
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
		void DecrementFloorsToFall() { if(m_FloorsToFall > 0) --m_FloorsToFall; }
		int GetFalling() const { return m_FloorsToFall; }


	private:
		std::string m_Type;
		int m_Id;

		bool m_IsPressed;
		int m_FloorsToFall;

		void HandleFall();
		void HandlePress();
		void ExecuteFall(float elapsedSec);
		void HandleIngredient(GameObject* pOther);
	};
}

