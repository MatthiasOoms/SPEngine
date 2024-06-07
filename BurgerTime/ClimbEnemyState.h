#ifndef CLIMBENEMYSTATE_H
#define CLIMBENEMYSTATE_H
#include "EnemyState.h"

namespace dae
{
	class ClimbEnemyState final : public EnemyState
	{
	public:
		ClimbEnemyState(GameObject* pPlayer, GameObject* pLadder, float speed);

		virtual void Update(float elapsedSec) override;
		virtual void Render(float elapsedSec) override;

		float GetSpeed() const { return m_Speed; }

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		GameObject* m_pLadder;
		float m_Speed;
	};
}

#endif // ! CLIMBENEMYSTATE_H
