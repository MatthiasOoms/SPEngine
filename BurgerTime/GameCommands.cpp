#include "GameCommands.h"
#include "GameObject.h"
#include "ScoreComponent.h"
#include "LivesComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "PlayerComponent.h"
#include "WalkPlayerState.h"
#include "IdlePlayerState.h"
#include "ClimbPlayerState.h"
#include <SoundServiceLocator.h>
#include <SoundSystem.h>
#include "PlatformComponent.h"

dae::WalkCommand::WalkCommand(GameObject* pGameObject, float speed)
	: Command{}
	, m_pGameObject{ pGameObject }
	, m_MoveSpeed{ speed }
{
}

void dae::WalkCommand::Execute(float elapsedSec)
{
	// Move on the x-axis
	GetGameObject()->SetLocalPosition(GetGameObject()->GetTransform().GetLocalPosition() + glm::vec3{ m_MoveSpeed * elapsedSec, 0, 0 });
}

dae::KillCommand::KillCommand(GameObject* pGameObject)
	: Command{ }
	, m_pGameObject{ pGameObject }
{
}

void dae::KillCommand::Execute(float)
{
	if (GetGameObject()->HasComponent<LivesComponent>())
	{
		GetGameObject()->GetComponent<LivesComponent>()->LowerLives();
	}
}

dae::ScoreSmallCommand::ScoreSmallCommand(GameObject* pGameObject)
	: Command{ }
	, m_pGameObject{ pGameObject }
{
}

void dae::ScoreSmallCommand::Execute(float)
{
	if (GetGameObject()->HasComponent<ScoreComponent>())
	{
		GetGameObject()->GetComponent<ScoreComponent>()->IncreaseScore(100);
	}
}

dae::SceneSwapCommand::SceneSwapCommand(std::string scene, std::string musicPath)
	: Command{}
	, m_Scene{ scene }
	, m_MusicPath{ musicPath }
{}

void dae::SceneSwapCommand::Execute(float)
{
	dae::SceneManager::GetInstance().SetActiveScene(GetScene());
	auto& soundSystem = dae::SoundServiceLocator::GetSoundSystem();
	dae::Sound temp{ GetMusicPath(), "Soundtrack", 1, -1};
	soundSystem.StopMusic();
	soundSystem.StopSoundEffects();

	soundSystem.PlayMusic(temp);
}

dae::WalkEndCommand::WalkEndCommand(GameObject* pGameObject)
	: Command{}
	, m_pGameObject{ pGameObject }
{
}

void dae::WalkEndCommand::Execute(float)
{
	if (GetGameObject()->HasComponent<PlayerComponent>())
	{
		auto stateComp = GetGameObject()->GetComponent<PlayerComponent>();
		if (dynamic_cast<IdlePlayerState*>(stateComp->GetCurrentState()) == nullptr)
		{
			stateComp->SetState(new IdlePlayerState{ GetGameObject() });
		}
	}
}

dae::WalkStartCommand::WalkStartCommand(GameObject* pGameObject)
	: Command{}
	, m_pGameObject{ pGameObject }
{
}

void dae::WalkStartCommand::Execute(float)
{
	if (GetGameObject()->HasComponent<PlayerComponent>())
	{
		auto stateComp = GetGameObject()->GetComponent<PlayerComponent>();
		if (dynamic_cast<WalkPlayerState*>(stateComp->GetCurrentState()) == nullptr)
		{
			stateComp->SetState(new WalkPlayerState{ GetGameObject() });
		}
	}
}

dae::ClimbStartCommand::ClimbStartCommand(GameObject* pGameObject)
	: Command{}
	, m_pGameObject{ pGameObject }
{
}

void dae::ClimbStartCommand::Execute(float)
{
	if (GetGameObject()->HasComponent<PlayerComponent>())
	{
		auto stateComp = GetGameObject()->GetComponent<PlayerComponent>();
		if (dynamic_cast<ClimbPlayerState*>(stateComp->GetCurrentState()) == nullptr)
		{
			stateComp->SetState(new ClimbPlayerState{ GetGameObject() });
		}
	}
}

dae::ClimbEndCommand::ClimbEndCommand(GameObject* pGameObject)
	: Command{}
	, m_pGameObject{ pGameObject }
{
}

void dae::ClimbEndCommand::Execute(float)
{
	if (GetGameObject()->HasComponent<PlayerComponent>())
	{
		auto stateComp = GetGameObject()->GetComponent<PlayerComponent>();
		if (dynamic_cast<IdlePlayerState*>(stateComp->GetCurrentState()) == nullptr)
		{
			stateComp->SetState(new IdlePlayerState{ GetGameObject() });
		}
	}
}

dae::ClimbCommand::ClimbCommand(GameObject* pGameObject, float speed)
	: Command{}
	, m_pGameObject{ pGameObject }
	, m_ClimbSpeed{ speed }
{
}

void dae::ClimbCommand::Execute(float elapsedSec)
{
	// Move on the y-axis
	GetGameObject()->SetLocalPosition(GetGameObject()->GetTransform().GetLocalPosition() + glm::vec3{ 0, m_ClimbSpeed * elapsedSec, 0 });
}