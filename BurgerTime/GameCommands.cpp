#include "PepperComponent.h"
#include "GameCommands.h"

// Enemy
#include "EnemyComponent.h"
#include "WalkingEnemyState.h"
#include "ClimbEnemyState.h"

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
	m_PeterWalkTexture = dae::ResourceManager::GetInstance().LoadTexture("PeterWalk.png");
}

void dae::WalkCommand::Execute(float elapsedSec)
{
	// Move on the x-axis
	bool canWalk = false;

	auto selfPos = GetGameObject()->GetTransform().GetWorldPosition();
	auto selfDims = GetGameObject()->GetTransform().GetDimensions();

	auto pPlatforms = SceneManager::GetInstance().GetActiveScene().GetObjectsByTag("Platform");

	float newY{};

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
				if (selfPos.y + selfDims.y >= platformPos.y - 3 && selfPos.y + selfDims.y <= platformPos.y + platformDims.y)
				{
					canWalk = true;
					newY = platformPos.y - selfDims.y;
					break;
				}
			}
		}
	}

	if (canWalk)
	{
		glm::vec3 temp{ GetGameObject()->GetTransform().GetLocalPosition() + glm::vec3{m_MoveSpeed* elapsedSec, 0, 0 } };
		temp.y = newY;
		GetGameObject()->SetLocalPosition(temp);
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
				GetGameObject()->GetComponent<TextureComponent>()->SetTexture(m_PeterWalkTexture);
				stateComp->SetState(new WalkPlayerState{ GetGameObject() });
			}
		}
	}
}

dae::FloatCommand::FloatCommand(GameObject* pGameObject, float speed)
	: Command{}
	, m_pGameObject{ pGameObject }
	, m_FloatSpeed{ speed }
{
}

void dae::FloatCommand::Execute(float elapsedSec)
{
	auto temp = GetGameObject()->GetTransform().GetLocalPosition();
	GetGameObject()->SetLocalPosition(temp + glm::vec3{ m_FloatSpeed * elapsedSec, 0, 0 });
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

dae::SceneSwapCommand::SceneSwapCommand(std::string scene, std::string musicPath)
	: Command{}
	, m_Scene{ scene }
	, m_MusicPath{ musicPath }
{}

void dae::SceneSwapCommand::Execute(float)
{
	auto& sceneManager = SceneManager::GetInstance();
	auto players = sceneManager.GetActiveScene().GetObjectsByTag("Player");
	if (!players.empty())
	{
		auto currentPlayer = players.front();

		int currentLives{};
		int currentScore{};
		int currentPepper{};

		if (currentPlayer)
		{
			currentLives = currentPlayer->GetComponent<LivesComponent>()->GetLives();
			currentScore = currentPlayer->GetComponent<ScoreComponent>()->GetScore();
			currentPepper = currentPlayer->GetComponent<PlayerComponent>()->GetPepperCount();
		}

		//Get player from next scene
		auto nextPlayers = sceneManager.GetScene(GetScene()).GetObjectsByTag("Player");
		if (!nextPlayers.empty())
		{
			auto nextPlayer = nextPlayers.front();
			if (nextPlayer)
			{
				nextPlayer->GetComponent<LivesComponent>()->SetLives(currentLives);
				nextPlayer->GetComponent<ScoreComponent>()->SetScore(currentScore);
				nextPlayer->GetComponent<PlayerComponent>()->SetPepperCount(currentPepper);
			}
		}
	}

	dae::SceneManager::GetInstance().SetActiveScene(GetScene());
	auto& soundSystem = dae::SoundServiceLocator::GetSoundSystem(); 
	
	soundSystem.StopMusic();
	soundSystem.StopSoundEffects();

	if (!GetMusicPath().empty())
	{
		dae::Sound temp{ GetMusicPath(), "Soundtrack", -1 };

		soundSystem.PlayMusic(temp);
	}
}

dae::WalkEndCommand::WalkEndCommand(GameObject* pGameObject)
	: Command{}
	, m_pGameObject{ pGameObject }
{
	m_PeterIdleTexture = dae::ResourceManager::GetInstance().LoadTexture("Peter.png");
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
				GetGameObject()->GetComponent<TextureComponent>()->SetTexture(m_PeterIdleTexture);
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
			pTextureComp->SetTexture(m_PeterWalkTexture);

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
	if (GetGameObject()->GetComponent<dae::EnemyComponent>())
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

		auto stateComp = GetGameObject()->GetComponent<dae::EnemyComponent>();

		if (dynamic_cast<dae::ClimbEnemyState*>(stateComp->GetCurrentState()) == nullptr)
		{
			if (dynamic_cast<dae::WalkingEnemyState*>(stateComp->GetCurrentState()) == nullptr)
			{
				// Set the texture to the Moving texture
				switch (stateComp->GetType())
				{
				case dae::EnemyType::Hotdog:
					pTextureComp->SetTexture(m_HotdogWalkTexture);
					break;
				case dae::EnemyType::Egg:
					pTextureComp->SetTexture(m_EggWalkTexture);
					break;
				case dae::EnemyType::Pickle:
					pTextureComp->SetTexture(m_PickleWalkTexture);
					break;
				default:
					break;
				}

				// Find closest player
				auto players = dae::SceneManager::GetInstance().GetActiveScene().GetObjectsByTag("Player");
				GameObject* pClosestPlayer{ players.front() };
				for (auto player : players)
				{
					// Calculate distance to player
					const auto playerPos{ pClosestPlayer->GetTransform().GetWorldPosition() };
					const auto newPlayerPos{ player->GetTransform().GetWorldPosition() };
					const auto distanceToPlayer{ (playerPos - GetGameObject()->GetTransform().GetWorldPosition()) };
					const auto newDistanceToPlayer{ (newPlayerPos - GetGameObject()->GetTransform().GetWorldPosition()) };

					// Save closest player
					if (glm::length(newDistanceToPlayer) < glm::length(distanceToPlayer))
					{
						pClosestPlayer = player;
					}
				}

				// Move towards nearest player ( speed = 75 if right, -75 if left)
				const auto playerPos{ pClosestPlayer->GetTransform().GetWorldPosition() };
				const auto enemyPos{ GetGameObject()->GetTransform().GetWorldPosition() };
				const auto direction{ playerPos - enemyPos };

				// Set speed
				float speed{};
				if (direction.x > 0)
				{
					speed = 75.f;
				}
				else
				{
					speed = -75.f;
				}

				// Set the state to walking
				stateComp->SetState(new dae::WalkingEnemyState{ GetGameObject(), speed });
			}
		}		
	}
}

dae::WalkStartCommand::WalkStartCommand(GameObject* pGameObject, float moveSpeed)
	: Command{}
	, m_pGameObject{ pGameObject }
	, m_MoveSpeed{ moveSpeed }
{
	m_PeterWalkTexture = dae::ResourceManager::GetInstance().LoadTexture("PeterWalk.png");
	m_HotdogWalkTexture = dae::ResourceManager::GetInstance().LoadTexture("HotdogWalk.png");
	m_EggWalkTexture = dae::ResourceManager::GetInstance().LoadTexture("EggWalk.png");
	m_PickleWalkTexture = dae::ResourceManager::GetInstance().LoadTexture("PickleWalk.png");
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
						GetGameObject()->GetComponent<TextureComponent>()->SetTexture(m_PeterClimbTexture);
					}
				}
			}
		}
	}
}

void dae::ClimbStartCommand::HandleEnemy()
{
	if (GetGameObject()->GetComponent<dae::EnemyComponent>())
	{
		// Get enemy TextureComponent
		auto pTextureComp = GetGameObject()->GetComponent<TextureComponent>();
		auto stateComp = GetGameObject()->GetComponent<dae::EnemyComponent>();

		// Change state
		stateComp->SetState(new dae::ClimbEnemyState{ GetGameObject(), m_pLadder, m_MoveSpeed });

		switch (stateComp->GetType())
		{
		case dae::EnemyType::Hotdog:
			pTextureComp->SetTexture(m_HotdogClimbTexture);
			break;
		case dae::EnemyType::Egg:
			pTextureComp->SetTexture(m_EggClimbTexture);
			break;
		case dae::EnemyType::Pickle:
			pTextureComp->SetTexture(m_PickleClimbTexture);
			break;
		default:
			break;
		}
	}
}

dae::ClimbStartCommand::ClimbStartCommand(GameObject* pGameObject, float moveSpeed)
	: Command{}
	, m_pGameObject{ pGameObject }
	, m_pLadder{ nullptr }
	, m_MoveSpeed{ moveSpeed }
{
	m_PeterClimbTexture = dae::ResourceManager::GetInstance().LoadTexture("PeterClimb.png");
	m_HotdogClimbTexture = dae::ResourceManager::GetInstance().LoadTexture("HotdogClimb.png");
	m_EggClimbTexture = dae::ResourceManager::GetInstance().LoadTexture("EggClimb.png");
	m_PickleClimbTexture = dae::ResourceManager::GetInstance().LoadTexture("PickleClimb.png");
}

dae::ClimbStartCommand::ClimbStartCommand(GameObject* pGameObject, GameObject* pLadder, float moveSpeed)
	: Command{}
	, m_pGameObject{ pGameObject }
	, m_pLadder{ pLadder }
	, m_MoveSpeed{ moveSpeed }
{
	m_PeterClimbTexture = dae::ResourceManager::GetInstance().LoadTexture("PeterClimb.png");
	m_HotdogClimbTexture = dae::ResourceManager::GetInstance().LoadTexture("HotdogClimb.png");
	m_EggClimbTexture = dae::ResourceManager::GetInstance().LoadTexture("EggClimb.png");
	m_PickleClimbTexture = dae::ResourceManager::GetInstance().LoadTexture("PickleClimb.png");
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
					GetGameObject()->GetComponent<TextureComponent>()->SetTexture(m_PeterIdleTexture);
					// Set the player state to idle
					stateComp->SetState(new IdlePlayerState{ GetGameObject() });
				}
			}
		}
	}
}

void dae::ClimbEndCommand::HandleEnemy()
{
	if (GetGameObject()->HasComponent<EnemyComponent>())
	{
		auto stateComp = GetGameObject()->GetComponent<EnemyComponent>();
		// Set texture to walk if touching platform
		for (auto& platform : dae::SceneManager::GetInstance().GetActiveScene().GetObjectsByTag("Platform"))
		{
			auto platformPos = platform->GetTransform().GetWorldPosition();
			auto platformDims = platform->GetTransform().GetDimensions();

			auto selfPos = GetGameObject()->GetTransform().GetWorldPosition();
			auto selfDims = GetGameObject()->GetTransform().GetDimensions();

			if (selfPos.x + selfDims.x >= platformPos.x && selfPos.x <= platformPos.x + platformDims.x)
			{
				if (selfPos.y + selfDims.y >= platformPos.y - 3 && selfPos.y + selfDims.y <= platformPos.y + platformDims.y)
				{
					// Set the texture to the Walk texture
					switch (stateComp->GetType())
					{
					case dae::EnemyType::Hotdog:
						GetGameObject()->GetComponent<TextureComponent>()->SetTexture(m_HotdogWalkTexture);
						break;
					case dae::EnemyType::Egg:
						GetGameObject()->GetComponent<TextureComponent>()->SetTexture(m_EggWalkTexture);
						break;
					case dae::EnemyType::Pickle:
						GetGameObject()->GetComponent<TextureComponent>()->SetTexture(m_PickleWalkTexture);
						break;
					}

					// Find closest player
					auto players = dae::SceneManager::GetInstance().GetActiveScene().GetObjectsByTag("Player");
					GameObject* pClosestPlayer{ players.front() };
					for (auto player : players)
					{
						// Calculate distance to player
						const auto playerPos{ pClosestPlayer->GetTransform().GetWorldPosition() };
						const auto newPlayerPos{ player->GetTransform().GetWorldPosition() };
						const auto distanceToPlayer{ (playerPos - GetGameObject()->GetTransform().GetWorldPosition()) };
						const auto newDistanceToPlayer{ (newPlayerPos - GetGameObject()->GetTransform().GetWorldPosition()) };

						// Save closest player
						if (glm::length(newDistanceToPlayer) < glm::length(distanceToPlayer))
						{
							pClosestPlayer = player;
						}
					}

					// Move towards nearest player ( speed = 75 if right, -75 if left)
					const auto playerPos{ pClosestPlayer->GetTransform().GetWorldPosition() };
					const auto enemyPos{ GetGameObject()->GetTransform().GetWorldPosition() };
					const auto direction{ playerPos - enemyPos };

					// Set speed
					float speed{};
					if (direction.x > 0)
					{
						speed = 75.f;
					}
					else
					{
						speed = -75.f;
					}

					// Set the state to walking
					stateComp->SetState(new dae::WalkingEnemyState{ GetGameObject(), speed });
				}
			}
		}
	}
}

dae::ClimbEndCommand::ClimbEndCommand(GameObject* pGameObject)
	: Command{}
	, m_pGameObject{ pGameObject }
{
	m_PeterIdleTexture = dae::ResourceManager::GetInstance().LoadTexture("Peter.png");
	m_HotdogWalkTexture = dae::ResourceManager::GetInstance().LoadTexture("HotdogWalk.png");
	m_EggWalkTexture = dae::ResourceManager::GetInstance().LoadTexture("EggWalk.png");
	m_PickleWalkTexture = dae::ResourceManager::GetInstance().LoadTexture("PickleWalk.png");
}

void dae::ClimbEndCommand::Execute(float)
{
	HandlePlayer();

	HandleEnemy();
}

dae::ClimbCommand::ClimbCommand(GameObject* pGameObject, float speed)
	: Command{}
	, m_pGameObject{ pGameObject }
	, m_ClimbSpeed{ speed }
{
	m_PeterIdleTexture = dae::ResourceManager::GetInstance().LoadTexture("Peter.png");
	m_HotdogWalkTexture = dae::ResourceManager::GetInstance().LoadTexture("HotdogWalk.png");
	m_EggWalkTexture = dae::ResourceManager::GetInstance().LoadTexture("EggWalk.png");
	m_PickleWalkTexture = dae::ResourceManager::GetInstance().LoadTexture("PickleWalk.png");
}

void dae::ClimbCommand::Execute(float elapsedSec)
{
	// Move on the y-axis
	bool canClimb = false;
	glm::vec3 endPos{};

	auto selfPos = GetGameObject()->GetTransform().GetWorldPosition();
	auto selfDims = GetGameObject()->GetTransform().GetDimensions();

	for (auto pLadder : dae::SceneManager::GetInstance().GetActiveScene().GetObjectsByTag("Ladder"))
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
		// ClimbEndCommand
		dae::ClimbEndCommand climbEndCommand{ GetGameObject() };
		climbEndCommand.Execute(elapsedSec);
	}
}

dae::SceneNextCommand::SceneNextCommand()
	: Command{}
{
}

void dae::SceneNextCommand::Execute(float)
{
	// Get the next scene and set it as the active scene
	auto& sceneManager = SceneManager::GetInstance();
	auto& activeScene = sceneManager.GetActiveScene().GetSceneName();
	auto& nextScene = sceneManager.GetNextScene(activeScene).GetSceneName();

	auto players = sceneManager.GetActiveScene().GetObjectsByTag("Player");
	if (!players.empty())
	{
		auto currentPlayer = players.front();

		int currentLives{};
		int currentScore{};
		int currentPepper{};

		if (currentPlayer)
		{
			currentLives = currentPlayer->GetComponent<LivesComponent>()->GetLives();
			currentScore = currentPlayer->GetComponent<ScoreComponent>()->GetScore();
			currentPepper = currentPlayer->GetComponent<PlayerComponent>()->GetPepperCount();
		}

		//Get player from next scene
		auto nextPlayers = sceneManager.GetNextScene(activeScene).GetObjectsByTag("Player");
		if (!nextPlayers.empty())
		{
			auto nextPlayer = nextPlayers.front();
			if (nextPlayer)
			{
				nextPlayer->GetComponent<LivesComponent>()->SetLives(currentLives);
				nextPlayer->GetComponent<ScoreComponent>()->SetScore(currentScore);
				nextPlayer->GetComponent<PlayerComponent>()->SetPepperCount(currentPepper);
			}
		}
	}

	sceneManager.SetActiveScene(nextScene);
}

dae::ToggleSoundCommand::ToggleSoundCommand()
	: Command{}
{
}

void dae::ToggleSoundCommand::Execute(float)
{
	auto& soundSystem = dae::SoundServiceLocator::GetSoundSystem();
	soundSystem.ToggleMute();
}

dae::FallCommand::FallCommand(GameObject* pGameObject, float speed)
	: Command{}
	, m_pGameObject{ pGameObject }
	, m_MoveSpeed{ speed }
{
}

void dae::FallCommand::Execute(float elapsedSec)
{
	GetGameObject()->SetLocalPosition(GetGameObject()->GetTransform().GetLocalPosition() + glm::vec3{ 0, m_MoveSpeed * elapsedSec, 0 });
}

dae::ThrowPepperCommand::ThrowPepperCommand(GameObject* pOwner)
	: Command{}
	, m_pGameObject{ pOwner }
{
}

void dae::ThrowPepperCommand::Execute(float)
{
	if (GetGameObject()->HasComponent<PlayerComponent>())
	{
		auto pepperComp = GetGameObject()->GetComponent<PlayerComponent>();
		pepperComp->ThrowPepper();
	}
}

dae::MultiplayerCommand::MultiplayerCommand()
	: Command{}
{
}

void dae::MultiplayerCommand::Execute(float)
{
	auto& sceneManager = SceneManager::GetInstance();
	sceneManager.SetActiveMultiplayerScene();
}

dae::VersusCommand::VersusCommand()
	: Command{}
{
}

void dae::VersusCommand::Execute(float)
{
	auto& sceneManager = SceneManager::GetInstance();
	sceneManager.SetActiveVersusScene();
}