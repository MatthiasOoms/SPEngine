#ifndef IDLE_PLAYER_STATE_H
#define IDLE_PLAYER_STATE_H
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

#endif // ! IDLE_PLAYER_STATE_H
