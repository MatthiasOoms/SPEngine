#pragma once

namespace dae
{
	class PlayerState
	{
	public:
		PlayerState() = default;
		virtual ~PlayerState() = default;

		PlayerState(const PlayerState& other) = delete;
		PlayerState(PlayerState&& other) = delete;
		PlayerState& operator=(const PlayerState& other) = delete;
		PlayerState& operator=(PlayerState&& other) = delete;

		virtual void Update(float elapsedSec) = 0;
		virtual void Render(float elapsedSec) = 0;

		virtual PlayerState* HandleState(float elapsedSec) = 0;

		virtual void OnEnter() = 0;
		virtual void OnExit() = 0;
	};
}
