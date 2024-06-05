#pragma once
#include <Component.h>
#include <TextureComponent.h>

namespace dae
{
    class EnemyState;

    class EggComponent : public Component
    {
    public:
        EggComponent(GameObject* pOwner);
        virtual ~EggComponent();

        EggComponent(const EggComponent& other) = delete;
        EggComponent(EggComponent&& other) = delete;
        EggComponent& operator=(const EggComponent& other) = delete;
        EggComponent& operator=(EggComponent&& other) = delete;

        virtual void Update(float elapsedSec) override;
        virtual void Render(float elapsedSec) const override;

        void SetState(EnemyState* pState);
        EnemyState* GetCurrentState() const { return m_pCurrentState; }

    private:
        EnemyState* m_pCurrentState;
    };
}

