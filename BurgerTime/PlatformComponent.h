#ifndef PLATFORMCOMPONENT_H
#define PLATFORMCOMPONENT_H
#include "Component.h"
#include <vector>
#include <string>

namespace dae
{
	class GameObject;

	class PlatformComponent : public UpdateComponent
	{
	public:
		PlatformComponent(GameObject* pOwner);
		virtual ~PlatformComponent() = default;

		PlatformComponent(const PlatformComponent& other) = delete;
		PlatformComponent(PlatformComponent&& other) = delete;
		PlatformComponent& operator=(const PlatformComponent& other) = delete;
		PlatformComponent& operator=(PlatformComponent&& other) = delete;

		virtual void Update(float elapsedSec) override;
		void RegisterObjects();
		void RegisterObjects(std::string scene);
	private:
		void HandleCollision(GameObject* pCollider);
		void HandleFallCollision(GameObject* pCollider);
		void HandleIngredientCollision(GameObject* pCollider);

		std::vector<GameObject*> m_pPlayers;
		std::vector<GameObject*> m_pEnemies;
		std::vector<GameObject*> m_pIngredients;

		bool m_EnemyPassedThrough;
	};
}

#endif // ! PLATFORMCOMPONENT_H
