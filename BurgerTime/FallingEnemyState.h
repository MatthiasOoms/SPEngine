#ifndef FALLINGENEMYSTATE_H
#define FALLINGENEMYSTATE_H
#include "EnemyState.h"

namespace dae
{
	class FallingEnemyState : public EnemyState
	{
	public:
		FallingEnemyState(GameObject* pSelf);
		FallingEnemyState(GameObject* pSelf, float speed);
		virtual ~FallingEnemyState() = default;

		FallingEnemyState(const FallingEnemyState& other) = delete;
		FallingEnemyState(FallingEnemyState&& other) = delete;
		FallingEnemyState& operator=(const FallingEnemyState& other) = delete;
		FallingEnemyState& operator=(FallingEnemyState&& other) = delete;

		virtual void Update(float elapsedSec) override;
		virtual void Render(float elapsedSec) const override;
		virtual void OnEnter() override;
		virtual void OnExit() override;

		void SetFloorsToFall(int floors);
		int GetFloorsToFall() const { return m_FloorsToFall; }

	private:
		float m_FallSpeed;
		int m_FloorsToFall;
	};
}

#endif // ! FALLINGENEMYSTATE_H
