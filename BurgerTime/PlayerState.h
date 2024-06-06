#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

namespace dae
{
	class GameObject;

	class PlayerState
	{
	public:
		PlayerState(GameObject* player);
		virtual ~PlayerState() = default;

		PlayerState(const PlayerState& other) = delete;
		PlayerState(PlayerState&& other) = delete;
		PlayerState& operator=(const PlayerState& other) = delete;
		PlayerState& operator=(PlayerState&& other) = delete;

		virtual void Update(float elapsedSec) = 0;
		virtual void Render(float elapsedSec) = 0;

		virtual void OnEnter() = 0;
		virtual void OnExit() = 0;

	protected:
		GameObject* GetPlayer() const { return m_pPlayer; }

	private:
		GameObject* m_pPlayer;
	};
}

#endif // ! PLAYER_STATE_H
