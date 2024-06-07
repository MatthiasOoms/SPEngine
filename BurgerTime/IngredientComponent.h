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

		void Reset();
		bool GetPressed() const { return m_IsPressed; }

		void SetFalling(bool falling) { m_IsFalling = falling; }
		bool GetFalling() const { return m_IsFalling; }


	private:
		std::string m_Type;
		int m_Id;

		bool m_IsPressed;
		bool m_IsFalling;

		void HandlePress();
		void HandleFall(float elapsedSec);
		void HandleIngredient(GameObject* pOther);
	};
}

