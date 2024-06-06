#ifndef HOTDOGCOMPONENT_H
#define HOTDOGCOMPONENT_H
#include <Component.h>
#include <TextureComponent.h>

namespace dae
{
    class EnemyState;

    class HotdogComponent : public Component
    {
    public:
        HotdogComponent(GameObject* pOwner);
        virtual ~HotdogComponent();

        HotdogComponent(const HotdogComponent& other) = delete;
        HotdogComponent(HotdogComponent&& other) = delete;
        HotdogComponent& operator=(const HotdogComponent& other) = delete;
        HotdogComponent& operator=(HotdogComponent&& other) = delete;

        virtual void Update(float elapsedSec) override;
        virtual void Render(float elapsedSec) const override;

        void SetState(EnemyState* pState);
        EnemyState* GetCurrentState() const { return m_pCurrentState; }

    private:
        EnemyState* m_pCurrentState;
    };
}

#endif // ! HOTDOGCOMPONENT_H
