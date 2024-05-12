#pragma once
#include <memory>
#include "PlayerState.h"
#include "Singleton.h"

namespace dae
{
	class PlayerStateManager final : public Singleton<PlayerStateManager>
	{
	public:
		PlayerStateManager(const PlayerStateManager& other) = delete;
		PlayerStateManager(PlayerStateManager&& other) = delete;
		PlayerStateManager& operator=(const PlayerStateManager& other) = delete;
		PlayerStateManager& operator=(PlayerStateManager&& other) = delete;

		void Update(float elapsedSec);
		void Render(float elapsedSec);

		std::shared_ptr<PlayerState> GetCurrentState() const { return m_pCurrentState; }

	private:
		std::shared_ptr<PlayerState> m_pCurrentState;
	};
}

