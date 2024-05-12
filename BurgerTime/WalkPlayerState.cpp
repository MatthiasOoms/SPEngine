#include "WalkPlayerState.h"
#include "IdlePlayerState.h"
#include "InputManager.h"
#include "GameObject.h"
#include <SDL_scancode.h>

dae::WalkPlayerState::WalkPlayerState(GameObject* pPlayer)
	: PlayerState(pPlayer)
{
}

void dae::WalkPlayerState::Update(float)
{
}

void dae::WalkPlayerState::Render(float)
{
}

void dae::WalkPlayerState::OnEnter()
{
}

void dae::WalkPlayerState::OnExit()
{
}
