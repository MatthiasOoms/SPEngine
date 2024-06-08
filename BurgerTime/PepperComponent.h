#ifndef PEPPERCOMPONENT_H
#define PEPPERCOMPONENT_H
#include "Component.h"

namespace dae
{
	class GameObject;

	class PepperComponent : public UpdateComponent
	{
	public:
		PepperComponent(GameObject* pOwner);
		virtual ~PepperComponent() = default;

		PepperComponent(const PepperComponent& other) = delete;
		PepperComponent(PepperComponent&& other) = delete;
		PepperComponent& operator=(const PepperComponent& other) = delete;
		PepperComponent& operator=(PepperComponent&& other) = delete;

		virtual void Update(float elapsedSec) override;

		void ThrowPepper();

	private:
		float m_PepperCooldown;
		float m_AccumulatedTime;
	};
}

#endif // ! PEPPERCOMPONENT_H
