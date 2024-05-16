#include "IdlePlayerState.h"
#include "WalkPlayerState.h"
#include "InputManager.h"
#include "GameObject.h"
#include <SDL_scancode.h>
#include <iostream>

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
	std::cout << "Start Idle\n";
}

void dae::IdlePlayerState::OnExit()
{
	std::cout << "End Idle\n";
}
