#ifndef ENEMYCOMPONENT_H
#define ENEMYCOMPONENT_H
#include <Component.h>
#include <memory>
#include "Texture2D.h"

namespace dae
{
    class EnemyState;

    enum struct EnemyType
    {
        Hotdog,
		Egg,
		Pickle
    };

    class EnemyComponent : public Component
    {
    public:
        EnemyComponent(GameObject* pOwner);
        virtual ~EnemyComponent();

        EnemyComponent(const EnemyComponent& other) = delete;
        EnemyComponent(EnemyComponent&& other) = delete;
        EnemyComponent& operator=(const EnemyComponent& other) = delete;
        EnemyComponent& operator=(EnemyComponent&& other) = delete;

        virtual void Update(float elapsedSec) override;
        virtual void Render(float elapsedSec) const override;

        void SetState(EnemyState* pState);
        EnemyState* GetCurrentState() const { return m_pCurrentState; }
        EnemyType GetType() const { return m_Type; }
        void SetType(EnemyType type);

		bool IsStunned() const { return m_IsStunned; }
        void Stun();

        void Respawn();

        void SetControlled(bool isControlled) { m_IsControlled = isControlled; }
        bool GetIsControlled() { return m_IsControlled; }

    private:
        EnemyState* m_pCurrentState;
        EnemyType m_Type;

		std::shared_ptr<Texture2D> m_pHotdogStunned;
		std::shared_ptr<Texture2D> m_pEggStunned;
		std::shared_ptr<Texture2D> m_pPickleStunned;

		bool m_IsStunned;
		float m_StunDuration;
		float m_AccumulatedTime;

        bool m_IsControlled;

		std::shared_ptr<Texture2D> m_pPreStunTexture;
    };
}

#endif // ! PICKLECOMPONENT_H
