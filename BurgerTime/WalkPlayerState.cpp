#include "WalkPlayerState.h"
#include "IdlePlayerState.h"
#include "InputManager.h"
#include "GameObject.h"
#include <SDL_scancode.h>
#include <iostream>

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
	std::cout << "Start Walk\n";
}

void dae::WalkPlayerState::OnExit()
{
	std::cout << "End Walk\n";
}