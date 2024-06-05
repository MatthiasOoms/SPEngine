#pragma once

namespace dae
{
	class GameObject;

	class EnemyState
	{
	public:
		EnemyState(GameObject* player);
		virtual ~EnemyState() = default;

		EnemyState(const EnemyState& other) = delete;
		EnemyState(EnemyState&& other) = delete;
		EnemyState& operator=(const EnemyState& other) = delete;
		EnemyState& operator=(EnemyState&& other) = delete;

		virtual void Update(float elapsedSec) = 0;
		virtual void Render(float elapsedSec) = 0;

		virtual void OnEnter() = 0;
		virtual void OnExit() = 0;

	protected:
		GameObject* GetEnemy() const { return m_pEnemy; }

	private:
		GameObject* m_pEnemy;
	};
}
