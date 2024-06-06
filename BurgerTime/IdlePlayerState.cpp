#include "IdlePlayerState.h"
#include "PlayerState.h"
#include "GameObject.h"

dae::IdlePlayerState::IdlePlayerState(GameObject* pPlayer)
	: PlayerState(pPlayer)
{
}

void dae::IdlePlayerState::Update(float)
{
}

void dae::IdlePlayerState::Render(float)
{
}

void dae::IdlePlayerState::OnEnter()
{
}

void dae::IdlePlayerState::OnExit()
{
}
