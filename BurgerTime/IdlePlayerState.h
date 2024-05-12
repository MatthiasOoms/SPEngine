#pragma once
#include "PlayerState.h"

namespace dae
{
	class IdlePlayerState final : public PlayerState
	{
	public:
		IdlePlayerState(GameObject* pPlayer);

		virtual void Update(float elapsedSec) override;
		virtual void Render(float elapsedSec) override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
	};
}

