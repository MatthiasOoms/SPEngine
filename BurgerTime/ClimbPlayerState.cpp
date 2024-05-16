#include "ClimbPlayerState.h"
#include "InputManager.h"
#include "GameObject.h"
#include <SDL_scancode.h>
#include <iostream>

dae::ClimbPlayerState::ClimbPlayerState(GameObject* pPlayer)
	: PlayerState(pPlayer)
{
}

void dae::ClimbPlayerState::Update(float)
{
}

void dae::ClimbPlayerState::Render(float)
{
}

void dae::ClimbPlayerState::OnEnter()
{
	std::cout << "Start Climb\n";
}

void dae::ClimbPlayerState::OnExit()
{
	std::cout << "End Climb\n";
}
