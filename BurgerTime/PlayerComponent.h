#ifndef PLAYERCOMPONENT_H
#define PLAYERCOMPONENT_H
#include <Component.h>
#include <vector>
#include <string>

namespace dae
{
    class PlayerState;
	class GameObject;

	class PlayerComponent : public Component
	{
    public:
        PlayerComponent(GameObject* pOwner);
        virtual ~PlayerComponent();

        PlayerComponent(const PlayerComponent& other) = delete;
        PlayerComponent(PlayerComponent&& other) = delete;
        PlayerComponent& operator=(const PlayerComponent& other) = delete;
        PlayerComponent& operator=(PlayerComponent&& other) = delete;

        virtual void Update(float elapsedSec) override;
        virtual void Render(float elapsedSec) const override;

		void SetState(PlayerState* pState);
        PlayerState* GetCurrentState() const { return m_pCurrentState; }

		void ThrowPepper();

        void RegisterObjects();
		void RegisterObjects(std::string sceneName);

		int GetPepperCount() const { return m_PepperCount; }
		void SetPepperCount(int pepperCount) { m_PepperCount = pepperCount; }

    private:
        PlayerState* m_pCurrentState;

		std::vector<GameObject*> m_pEnemies;

		int m_PepperCount;
		float m_PepperCooldown;
		float m_AccumulatedPepperTime;

		float m_HurtCooldown;
		float m_AccumulatedHurtTime;
    };
}

#endif // ! PLAYERCOMPONENT_H
