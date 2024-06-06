#include "GameCommands.h"

// Enemy
#include "HotdogComponent.h"
#include "WalkingEnemyState.h"
#include "ClimbEnemyState.h"
#include "EggComponent.h"
#include "PickleComponent.h"

// Engine
#include "GameObject.h"
#include <SoundSystem.h>
#include <SoundServiceLocator.h>
#include <ResourceManager.h>
#include <SceneManager.h>
#include <Scene.h>

// Player
#include "PlayerComponent.h"
#include "WalkPlayerState.h"
#include "ClimbPlayerState.h"
#include "IdlePlayerState.h"

// Components
#include "TextureComponent.h"
#include "LivesComponent.h"
#include "ScoreComponent.h"

// Platform
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
	bool canWalk = false;

	auto selfPos = GetGameObject()->GetTransform().GetWorldPosition();
	auto selfDims = GetGameObject()->GetTransform().GetDimensions();

	auto pPlatforms = SceneManager::GetInstance().GetActiveScene().GetObjectsByTag("Platform");
	for (auto pPlatform : pPlatforms)
	{
		// Get the player's position and dimensions
		auto platformPos = pPlatform->GetTransform().GetWorldPosition();
		auto platformDims = pPlatform->GetTransform().GetDimensions();

		// If self left is in the object
		if (selfPos.x <= platformPos.x + platformDims.x && selfPos.x >= platformPos.x)
		{
			// If self right is in the object
			if (selfPos.x + selfDims.x <= platformPos.x + platformDims.x && selfPos.x + selfDims.x >= platformPos.x)
			{
				// If self is above the object and has some overlap with the platform object on the y-axis
				if (selfPos.y + selfDims.y >= platformPos.y && selfPos.y + selfDims.y <= platformPos.y + platformDims.y)
				{
					canWalk = true;
				}
			}
		}
	}

	if (canWalk)
	{
		GetGameObject()->SetLocalPosition(GetGameObject()->GetTransform().GetLocalPosition() + glm::vec3{ m_MoveSpeed * elapsedSec, 0, 0 });
	}

	// Get the PlayerComponent
	if (GetGameObject()->HasComponent<PlayerComponent>())
	{
		auto stateComp = GetGameObject()->GetComponent<PlayerComponent>();
		// If the player is not walking or climbing, set the state to walking
		if (dynamic_cast<WalkPlayerState*>(stateComp->GetCurrentState()) == nullptr)
		{
			if (dynamic_cast<ClimbPlayerState*>(stateComp->GetCurrentState()) == nullptr)
			{
				// Set texture to PeterWalk if not already
				GetGameObject()->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("PeterWalk.png"));
				stateComp->SetState(new WalkPlayerState{ GetGameObject() });
			}
		}
	}
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

dae::HotdogKilledCommand::HotdogKilledCommand(GameObject* pGameObject)
	: Command{ }
	, m_pGameObject{ pGameObject }
{
}

void dae::HotdogKilledCommand::Execute(float)
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
	dae::Sound temp{ GetMusicPath(), "Soundtrack", -1};
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
		// If the player is not idle or climbing, set the state to idle
		if (dynamic_cast<IdlePlayerState*>(stateComp->GetCurrentState()) == nullptr)
		{
			if (dynamic_cast<ClimbPlayerState*>(stateComp->GetCurrentState()) == nullptr)
			{
				// Set the player state to idle
				stateComp->SetState(new IdlePlayerState{ GetGameObject() });

				// Set the player texture to the Idle texture
				GetGameObject()->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Peter.png"));
			}
		}
	}
}

void dae::WalkStartCommand::HandlePlayer()
{
	if (!GetGameObject()->HasComponent<PlayerComponent>())
	{
		return;
	}

	auto stateComp = GetGameObject()->GetComponent<PlayerComponent>();
	// If the player is not walking or climbing, set the state to walking
	if (dynamic_cast<WalkPlayerState*>(stateComp->GetCurrentState()) == nullptr)
	{
		if (dynamic_cast<ClimbPlayerState*>(stateComp->GetCurrentState()) == nullptr)
		{
			stateComp->SetState(new WalkPlayerState{ GetGameObject() });

			// Get player TextureComponent
			auto pTextureComp = GetGameObject()->GetComponent<TextureComponent>();

			// Set the player texture to the Moving texture
			pTextureComp->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("PeterWalk.png"));

			if (m_MoveSpeed > 0)
			{
				pTextureComp->SetScale(abs(pTextureComp->GetScale()));
			}
			else
			{
				pTextureComp->SetScale(-abs(pTextureComp->GetScale()));
			}
		}
	}
}

void dae::WalkStartCommand::HandleEnemy()
{
	// Get enemy TextureComponent
	auto pTextureComp = GetGameObject()->GetComponent<TextureComponent>();
	if (m_MoveSpeed > 0)
	{
		pTextureComp->SetScale(abs(pTextureComp->GetScale()));
	}
	else
	{
		pTextureComp->SetScale(-abs(pTextureComp->GetScale()));
	}

	if (GetGameObject()->GetComponent<dae::HotdogComponent>())
	{
		auto stateComp = GetGameObject()->GetComponent<dae::HotdogComponent>();
		if (dynamic_cast<dae::ClimbEnemyState*>(stateComp->GetCurrentState()) == nullptr)
		{
			if (dynamic_cast<dae::WalkingEnemyState*>(stateComp->GetCurrentState()) == nullptr)
			{
				// Set texture to HotdogWalk.png
				pTextureComp->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("HotdogWalk.png"));
				stateComp->SetState(new dae::WalkingEnemyState{ GetGameObject() });
			}
		}		
	}
	else if (GetGameObject()->GetComponent<dae::EggComponent>())
	{
		auto stateComp = GetGameObject()->GetComponent<dae::EggComponent>();
		if (dynamic_cast<dae::ClimbEnemyState*>(stateComp->GetCurrentState()) == nullptr)
		{
			if (dynamic_cast<dae::WalkingEnemyState*>(stateComp->GetCurrentState()) == nullptr)
			{
				pTextureComp->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("EggWalk.png"));
				stateComp->SetState(new dae::WalkingEnemyState{ GetGameObject() });
			}
		}
	}
	else if (GetGameObject()->GetComponent<dae::PickleComponent>())
	{
		auto stateComp = GetGameObject()->GetComponent<dae::PickleComponent>();
		if (dynamic_cast<dae::ClimbEnemyState*>(stateComp->GetCurrentState()) == nullptr)
		{
			if (dynamic_cast<dae::WalkingEnemyState*>(stateComp->GetCurrentState()) == nullptr)
			{
				pTextureComp->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("PickleWalk.png"));
				stateComp->SetState(new dae::WalkingEnemyState{ GetGameObject() });
			}
		}
	}
}

dae::WalkStartCommand::WalkStartCommand(GameObject* pGameObject, float moveSpeed)
	: Command{}
	, m_pGameObject{ pGameObject }
	, m_MoveSpeed{ moveSpeed }
{
}

void dae::WalkStartCommand::Execute(float)
{
	// Get the PlayerComponent
	HandlePlayer();

	// Do the same for the enemies.
	HandleEnemy();
}

void dae::ClimbStartCommand::HandlePlayer()
{
	if (GetGameObject()->HasComponent<PlayerComponent>())
	{
		// If the player is not climbing, set the state to climbing
		auto stateComp = GetGameObject()->GetComponent<PlayerComponent>();
		if (dynamic_cast<ClimbPlayerState*>(stateComp->GetCurrentState()) == nullptr)
		{
			// If the player is touching a ladder, set the state to climbing
			for (auto& ladder : dae::SceneManager::GetInstance().GetActiveScene().GetObjectsByTag("Ladder"))
			{
				auto ladderPos = ladder->GetTransform().GetWorldPosition();
				auto ladderDims = ladder->GetTransform().GetDimensions();

				auto selfPos = GetGameObject()->GetTransform().GetWorldPosition();
				auto selfDims = GetGameObject()->GetTransform().GetDimensions();

				if (selfPos.x + selfDims.x >= ladderPos.x && selfPos.x <= ladderPos.x + ladderDims.x)
				{
					if (selfPos.y + selfDims.y >= ladderPos.y && selfPos.y <= ladderPos.y + ladderDims.y)
					{
						stateComp->SetState(new ClimbPlayerState{ GetGameObject() });
						GetGameObject()->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("PeterClimb.png"));
					}
				}
			}
		}
	}
}

void dae::ClimbStartCommand::HandleEnemy()
{
	// Get enemy TextureComponent
	auto pTextureComp = GetGameObject()->GetComponent<TextureComponent>();

	if (GetGameObject()->GetComponent<dae::HotdogComponent>())
	{
		auto stateComp = GetGameObject()->GetComponent<dae::HotdogComponent>();
		stateComp->SetState(new dae::ClimbEnemyState{ GetGameObject(), m_MoveSpeed });

		pTextureComp->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("HotdogClimb.png"));
	}
	else if (GetGameObject()->GetComponent<dae::EggComponent>())
	{
		auto stateComp = GetGameObject()->GetComponent<dae::EggComponent>();
		stateComp->SetState(new dae::ClimbEnemyState{ GetGameObject(), m_MoveSpeed });

		// Set the player texture to the Moving texture
		pTextureComp->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("EggClimb.png"));
	}
	else if (GetGameObject()->GetComponent<dae::PickleComponent>())
	{
		auto stateComp = GetGameObject()->GetComponent<dae::PickleComponent>();
		stateComp->SetState(new dae::ClimbEnemyState{ GetGameObject(), m_MoveSpeed });

		// Set the player texture to the Moving texture
		pTextureComp->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("PickleClimb.png"));
	}
}

dae::ClimbStartCommand::ClimbStartCommand(GameObject* pGameObject, float moveSpeed)
	: Command{}
	, m_pGameObject{ pGameObject }
	, m_MoveSpeed{ moveSpeed }
{
}

void dae::ClimbStartCommand::Execute(float)
{
	HandlePlayer();
	HandleEnemy();
}

void dae::ClimbEndCommand::HandlePlayer()
{
	if (GetGameObject()->HasComponent<PlayerComponent>())
	{
		auto stateComp = GetGameObject()->GetComponent<PlayerComponent>();
		// Set texture to idle if touching platform
		for (auto& platform : dae::SceneManager::GetInstance().GetActiveScene().GetObjectsByTag("Platform"))
		{
			auto platformPos = platform->GetTransform().GetWorldPosition();
			auto platformDims = platform->GetTransform().GetDimensions();

			auto selfPos = GetGameObject()->GetTransform().GetWorldPosition();
			auto selfDims = GetGameObject()->GetTransform().GetDimensions();

			if (selfPos.x + selfDims.x >= platformPos.x && selfPos.x <= platformPos.x + platformDims.x)
			{
				if (selfPos.y + selfDims.y >= platformPos.y && selfPos.y + selfDims.y <= platformPos.y + platformDims.y)
				{
					// Set the player texture to the Idle texture
					GetGameObject()->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Peter.png"));
					// Set the player state to idle
					stateComp->SetState(new IdlePlayerState{ GetGameObject() });
				}
			}
		}
	}
}

void dae::ClimbEndCommand::HandleEnemy()
{
	if (GetGameObject()->HasComponent<HotdogComponent>())
	{
		auto stateComp = GetGameObject()->GetComponent<HotdogComponent>();
		// Set texture to idle if touching platform
		for (auto& platform : dae::SceneManager::GetInstance().GetActiveScene().GetObjectsByTag("Platform"))
		{
			auto platformPos = platform->GetTransform().GetWorldPosition();
			auto platformDims = platform->GetTransform().GetDimensions();

			auto selfPos = GetGameObject()->GetTransform().GetWorldPosition();
			auto selfDims = GetGameObject()->GetTransform().GetDimensions();

			if (selfPos.x + selfDims.x >= platformPos.x && selfPos.x <= platformPos.x + platformDims.x)
			{
				if (selfPos.y + selfDims.y >= platformPos.y && selfPos.y + selfDims.y <= platformPos.y + platformDims.y)
				{
					// Set the player texture to the Idle texture
					GetGameObject()->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Peter.png"));
					// Set the player state to idle
					stateComp->SetState(new WalkingEnemyState{ GetGameObject() });
				}
			}
		}
	}
	// If enemy is Egg
	else if (GetGameObject()->HasComponent<EggComponent>())
	{
		auto stateComp = GetGameObject()->GetComponent<EggComponent>();
		// Set texture to idle if touching platform
		for (auto& platform : dae::SceneManager::GetInstance().GetActiveScene().GetObjectsByTag("Platform"))
		{
			auto platformPos = platform->GetTransform().GetWorldPosition();
			auto platformDims = platform->GetTransform().GetDimensions();

			auto selfPos = GetGameObject()->GetTransform().GetWorldPosition();
			auto selfDims = GetGameObject()->GetTransform().GetDimensions();

			if (selfPos.x + selfDims.x >= platformPos.x && selfPos.x <= platformPos.x + platformDims.x)
			{
				if (selfPos.y + selfDims.y >= platformPos.y && selfPos.y + selfDims.y <= platformPos.y + platformDims.y)
				{
					// Set the player texture to the Idle texture
					GetGameObject()->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Peter.png"));
					// Set the player state to idle
					stateComp->SetState(new WalkingEnemyState{ GetGameObject() });
				}
			}
		}
	}
	else if (GetGameObject()->HasComponent<PickleComponent>())
	{
		auto stateComp = GetGameObject()->GetComponent<PickleComponent>();
		// Set texture to idle if touching platform
		for (auto& platform : dae::SceneManager::GetInstance().GetActiveScene().GetObjectsByTag("Platform"))
		{
			auto platformPos = platform->GetTransform().GetWorldPosition();
			auto platformDims = platform->GetTransform().GetDimensions();

			auto selfPos = GetGameObject()->GetTransform().GetWorldPosition();
			auto selfDims = GetGameObject()->GetTransform().GetDimensions();

			if (selfPos.x + selfDims.x >= platformPos.x && selfPos.x <= platformPos.x + platformDims.x)
			{
				if (selfPos.y + selfDims.y >= platformPos.y && selfPos.y + selfDims.y <= platformPos.y + platformDims.y)
				{
					// Set the player texture to the Idle texture
					GetGameObject()->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Peter.png"));
					// Set the player state to idle
					stateComp->SetState(new WalkingEnemyState{ GetGameObject() });
				}
			}
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
	HandlePlayer();

	// Handle enemies
	if (GetGameObject()->HasComponent<dae::HotdogComponent>())
	{
		auto stateComp = GetGameObject()->GetComponent<HotdogComponent>();
		stateComp->SetState(new WalkingEnemyState{ GetGameObject() });
	}
	else if (GetGameObject()->HasComponent<dae::EggComponent>())
	{
		auto stateComp = GetGameObject()->GetComponent<EggComponent>();
		stateComp->SetState(new WalkingEnemyState{ GetGameObject() });
	}
	else if (GetGameObject()->HasComponent<dae::PickleComponent>())
	{
		auto stateComp = GetGameObject()->GetComponent<PickleComponent>();
		stateComp->SetState(new WalkingEnemyState{ GetGameObject() });
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
	bool canClimb = false;
	glm::vec3 endPos{};

	auto selfPos = GetGameObject()->GetTransform().GetWorldPosition();
	auto selfDims = GetGameObject()->GetTransform().GetDimensions();

	auto pLadders = SceneManager::GetInstance().GetActiveScene().GetObjectsByTag("Ladder");
	for (auto pLadder : pLadders)
	{
		// Get the player's position and dimensions
		auto ladderPos = pLadder->GetTransform().GetWorldPosition();
		auto ladderDims = pLadder->GetTransform().GetDimensions();

		// If Player center is in ladder
		if ((selfPos.x + (selfDims.x / 2) > ladderPos.x && selfPos.x + (selfDims.x / 2) < ladderPos.x + ladderDims.x))
		{
			// If bottom of player is in the ladder
			if (selfPos.y + selfDims.y >= ladderPos.y && selfPos.y + selfDims.y <= ladderPos.y + ladderDims.y)
			{
				auto temp = selfPos + glm::vec3{ 0, m_ClimbSpeed * elapsedSec, 0 };

				// If the new player bottom is in the ladder
				if (temp.y + selfDims.y >= ladderPos.y && temp.y + selfDims.y <= ladderPos.y + ladderDims.y)
				{
					endPos = temp;
					canClimb = true;
				}
			}
		}
	}

	if (canClimb)
	{
		GetGameObject()->SetLocalPosition(endPos);
	}
	else
	{
		// If the player is not touching a ladder, set the state to walking
		if (GetGameObject()->HasComponent<PlayerComponent>())
		{
			auto stateComp = GetGameObject()->GetComponent<PlayerComponent>();
			if (dynamic_cast<WalkPlayerState*>(stateComp->GetCurrentState()) == nullptr)
			{
				if (dynamic_cast<ClimbPlayerState*>(stateComp->GetCurrentState()) == nullptr)
				{
					// Set the player texture to the Moving texture
					GetGameObject()->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Peter.png"));
					stateComp->SetState(new IdlePlayerState{ GetGameObject() });
				}
			}
		}
		else if (GetGameObject()->HasComponent<HotdogComponent>())
		{
			auto stateComp = GetGameObject()->GetComponent<HotdogComponent>();
			if (dynamic_cast<WalkingEnemyState*>(stateComp->GetCurrentState()) == nullptr)
			{
				// Set the player texture to the Moving texture
				GetGameObject()->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("HotdogWalk.png"));
				stateComp->SetState(new WalkingEnemyState{ GetGameObject() });
			}
		}
		else if (GetGameObject()->HasComponent<EggComponent>())
		{
			auto stateComp = GetGameObject()->GetComponent<EggComponent>();
			if (dynamic_cast<WalkingEnemyState*>(stateComp->GetCurrentState()) == nullptr)
			{
				// Set the player texture to the Moving texture
				GetGameObject()->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("EggWalk.png"));
				stateComp->SetState(new WalkingEnemyState{ GetGameObject() });
			}
		}
		else if (GetGameObject()->HasComponent<PickleComponent>())
		{
			auto stateComp = GetGameObject()->GetComponent<PickleComponent>();
			if (dynamic_cast<WalkingEnemyState*>(stateComp->GetCurrentState()) == nullptr)
			{
				// Set the player texture to the Moving texture
				GetGameObject()->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("PickleWalk.png"));
				stateComp->SetState(new WalkingEnemyState{ GetGameObject() });
			}
		}
	}
}

dae::SceneNextCommand::SceneNextCommand()
{
}

void dae::SceneNextCommand::Execute(float)
{
	// Get the next scene and set it as the active scene
	auto& sceneManager = SceneManager::GetInstance();
	auto& activeScene = sceneManager.GetActiveScene().GetSceneName();
	auto& nextScene = sceneManager.GetNextScene(activeScene).GetSceneName();
	sceneManager.SetActiveScene(nextScene);
}

dae::ToggleSoundCommand::ToggleSoundCommand()
{
}

void dae::ToggleSoundCommand::Execute(float)
{
	auto& soundSystem = dae::SoundServiceLocator::GetSoundSystem();
	
	// If the game has been muted
	soundSystem.ToggleMute();
}
