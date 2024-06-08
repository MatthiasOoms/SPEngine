#ifndef PLAYERCOMPONENT_H
#define PLAYERCOMPONENT_H
#include <Component.h>

namespace dae
{
    class PlayerState;

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
    private:
        PlayerState* m_pCurrentState;

		int m_PepperCount;
		float m_PepperCooldown;
		float m_AccumulatedTime;
    };
}

#endif // ! PLAYERCOMPONENT_H
