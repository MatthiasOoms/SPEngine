#pragma once
#include "Component.h"

namespace dae
{
	class RotationComponent final : public dae::UpdateComponent
	{
	public:
		RotationComponent(GameObject* pOwner);
		~RotationComponent() = default;

		RotationComponent(const RotationComponent& other) = delete;
		RotationComponent(RotationComponent&& other) = delete;
		RotationComponent& operator=(const RotationComponent& other) = delete;
		RotationComponent& operator=(RotationComponent&& other) = delete;

		virtual void Update(float elapsedSec) override;
		virtual void Render(float) const override {};

		void SetRotationSpeed(float rotSpeed);

	private:
		float m_Distance;
		float m_RotSpeed;
		float m_RotAngle;

		float GetDistance(float x, float y, float z) const;
	};
}
