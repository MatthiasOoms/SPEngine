#include "PlayerStateManager.h"

void dae::PlayerStateManager::Update(float elapsedSec)
{
	m_pCurrentState->Update(elapsedSec);
}

void dae::PlayerStateManager::Render(float elapsedSec)
{
	m_pCurrentState->Render(elapsedSec);
}
