#include "GameCommands.h"
#include "GameObject.h"
#include "ScoreComponent.h"
#include "LivesComponent.h"
#include "SceneManager.h"
#include "PlayerComponent.h"
#include "WalkPlayerState.h"
#include "IdlePlayerState.h"
#include "ClimbPlayerState.h"
#include <SoundServiceLocator.h>
#include <SoundSystem.h>

dae::MoveCommand::MoveCommand(GameObject* pGameObject, glm::vec3 dir, float speed)
	: Command{}
	, m_pGameObject{ pGameObject }
	, m_MoveDir{ dir }
	, m_MoveSpeed{ speed }
{
}

void dae::MoveCommand::Execute(float elapsedSec)
{
	GetGameObject()->SetLocalPosition(GetGameObject()->GetTransform().GetLocalPosition() + (m_MoveDir * m_MoveSpeed * elapsedSec));
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
	SceneManager::GetInstance().SetActiveScene(GetScene());
	auto& soundSystem = SoundServiceLocator::GetSoundSystem();
	Sound temp{ GetMusicPath(), "Soundtrack", 1, -1};
	soundSystem.StopMusic();
	soundSystem.StopSoundEffects();

	soundSystem.PlayMusic(temp);
}

dae::MoveEndCommand::MoveEndCommand(GameObject* pGameObject)
	: Command{}
	, m_pGameObject{ pGameObject }
{
}

void dae::MoveEndCommand::Execute(float)
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

dae::MoveStartCommand::MoveStartCommand(GameObject* pGameObject)
	: Command{}
	, m_pGameObject{ pGameObject }
{
}

void dae::MoveStartCommand::Execute(float)
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
