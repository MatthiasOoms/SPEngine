#ifndef WALKINGENEMYSTATE_H
#define WALKINGENEMYSTATE_H
#include "EnemyState.h"

namespace dae
{
	class WalkingEnemyState final : public EnemyState
	{
	public:
		WalkingEnemyState(GameObject* pPlayer);

		virtual void Update(float elapsedSec) override;
		virtual void Render(float elapsedSec) override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		float m_Speed;

		GameObject* IsTouchingLadder();
	};
}

#endif // ! WALKINGENEMYSTATE_H
