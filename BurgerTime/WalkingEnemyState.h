#ifndef WALKINGENEMYSTATE_H
#define WALKINGENEMYSTATE_H
#include "EnemyState.h"

namespace dae
{
	class WalkingEnemyState final : public EnemyState
	{
	public:
		WalkingEnemyState(GameObject* pPlayer);
		WalkingEnemyState(GameObject* pPlayer, float speed);

		virtual void Update(float elapsedSec) override;
		virtual void Render(float elapsedSec) const override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		float m_Speed;
		float m_AccumulatedTime;
		float m_TimeToClimb;

		GameObject* IsTouchingLadder();
	};
}

#endif // ! WALKINGENEMYSTATE_H
