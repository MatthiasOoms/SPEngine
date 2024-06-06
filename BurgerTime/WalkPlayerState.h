#ifndef WALKPLAYERSTATE_H
#define WALKPLAYERSTATE_H
#include "PlayerState.h"

namespace dae
{
	class WalkPlayerState final : public PlayerState
	{
	public:
		WalkPlayerState(GameObject* pPlayer);

		virtual void Update(float elapsedSec) override;
		virtual void Render(float elapsedSec) override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
	};
}

#endif // ! WALKPLAYERSTATE_H
