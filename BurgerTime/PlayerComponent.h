#pragma once
#include <Component.h>
#include <TextureComponent.h>
#include "PlayerState.h"

namespace dae
{
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

        PlayerState* GetCurrentState() const { return m_pCurrentState; }

    private:
        PlayerState* m_pCurrentState;
    };
}

