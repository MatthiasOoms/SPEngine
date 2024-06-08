#ifndef PEPPERCOMPONENT_H
#define PEPPERCOMPONENT_H
#include "Component.h"
#include <vector>
#include <string>

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

		void RegisterObjects();
		void RegisterObjects(std::string sceneName);

	private:
		float m_PepperCooldown;
		float m_AccumulatedTime;

		std::vector<GameObject*> m_pEnemies;
	};
}

#endif // ! PEPPERCOMPONENT_H
