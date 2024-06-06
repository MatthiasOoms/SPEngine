#ifndef PICKLECOMPONENT_H
#define PICKLECOMPONENT_H
#include <Component.h>

namespace dae
{
    class EnemyState;

    class PickleComponent : public Component
    {
    public:
        PickleComponent(GameObject* pOwner);
        virtual ~PickleComponent();

        PickleComponent(const PickleComponent& other) = delete;
        PickleComponent(PickleComponent&& other) = delete;
        PickleComponent& operator=(const PickleComponent& other) = delete;
        PickleComponent& operator=(PickleComponent&& other) = delete;

        virtual void Update(float elapsedSec) override;
        virtual void Render(float elapsedSec) const override;

        void SetState(EnemyState* pState);
        EnemyState* GetCurrentState() const { return m_pCurrentState; }

    private:
        EnemyState* m_pCurrentState;
    };
}

#endif // ! PICKLECOMPONENT_H
