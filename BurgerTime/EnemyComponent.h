#ifndef ENEMYCOMPONENT_H
#define ENEMYCOMPONENT_H
#include <Component.h>

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

    private:
        EnemyState* m_pCurrentState;
        EnemyType m_Type;
    };
}

#endif // ! PICKLECOMPONENT_H
