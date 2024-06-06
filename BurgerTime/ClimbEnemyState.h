#ifndef CLIMBENEMYSTATE_H
#define CLIMBENEMYSTATE_H
#include "EnemyState.h"

namespace dae
{
	class ClimbEnemyState final : public EnemyState
	{
	public:
		ClimbEnemyState(GameObject* pPlayer);

		virtual void Update(float elapsedSec) override;
		virtual void Render(float elapsedSec) override;

		virtual void OnEnter() override;
		virtual void OnExit() override;
	};
}

#endif // ! CLIMBENEMYSTATE_H
