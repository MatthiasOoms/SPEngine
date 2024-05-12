#include "IdlePlayerState.h"
#include "WalkPlayerState.h"
#include "InputManager.h"
#include "GameObject.h"
#include <SDL_scancode.h>

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
