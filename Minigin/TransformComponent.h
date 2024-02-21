#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace dae
{
	class GameObject;

	class TransformComponent final : public Component
	{
	public:
		TransformComponent(GameObject* pOwner);
		~TransformComponent();

		virtual void Update(float) override {};
		virtual void Render(float) const override {};

		const glm::vec3& GetLocalPosition() const { return m_LocalPosition; }
		const glm::vec3& GetWorldPosition() const { return m_WorldPosition; }
		void SetLocalPosition(float x, float y, float z);
		void SetWorldPosition(float x, float y, float z);
	private:
		glm::vec3 m_LocalPosition;
		glm::vec3 m_WorldPosition;
	};
}
