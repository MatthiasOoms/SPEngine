#ifndef CLIMBPLAYERSTATE_H
#define CLIMBPLAYERSTATE_H
#include "PlayerState.h"

namespace dae
{
	class ClimbPlayerState final : public PlayerState
	{
	public:
		ClimbPlayerState(GameObject* pPlayer);

		virtual void Update(float elapsedSec) override;
		virtual void Render(float elapsedSec) override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
	};
}

#endif // ! CLIMBPLAYERSTATE_H
