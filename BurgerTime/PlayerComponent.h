#pragma once
#include <Component.h>
#include <TextureComponent.h>
#include "SceneManager.h"

namespace dae
{
    class CollisionComponent;
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

		void SetStaticLevel();

		void SetState(PlayerState* pState);
        PlayerState* GetCurrentState() const { return m_pCurrentState; }

    private:
        GameObject* m_pPlayer;
        PlayerState* m_pCurrentState;
		CollisionComponent* m_pPlayerDimensions;
        SceneManager& m_SceneManager;
		std::vector<GameObject*> m_pStaticLevel;
    };
}

