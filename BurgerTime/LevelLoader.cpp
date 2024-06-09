#include "ScoreObserverComponent.h"
#include "ScoreComponent.h"
#include "LivesObserverComponent.h"
#include "LivesComponent.h"
#include "PepperComponent.h"
#include <memory>
#include <string>
#include <fstream>
#include <TextureComponent.h>
#include <ResourceManager.h>
#include <InputManager.h>
#include "LevelLoader.h"
#include "GameObject.h"
#include <SceneManager.h>
#include <Scene.h>
#include "PlatformComponent.h"
#include "PlayerComponent.h"
#include "GameCommands.h"
#include "EnemyComponent.h"
#include "json.hpp" // nlohmann::json
#include <TextComponent.h>
#include "FPSComponent.h"
#include "IngredientComponent.h"
#include "PlateComponent.h"

void dae::LevelLoader::Init(const std::string& data)
{
	m_dataPath = data;
}

void dae::LevelLoader::LoadLevel(const std::string& fileName, const std::string& sceneName)
{
	// Create a vector of GameObjects
	std::vector<std::unique_ptr<dae::GameObject>> gameObjects{};
	auto& resources = dae::ResourceManager::GetInstance();
	auto& sceneManager = dae::SceneManager::GetInstance();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);

	// See if file ends in.json, if not add it
	std::string filePath;
	if (fileName.find(".json") == std::string::npos)
	{
		filePath = m_dataPath + "Levels/" + fileName + ".json";
	}
	else
	{
		filePath = m_dataPath + "Levels/" + fileName;
	}

	std::ifstream i(filePath);

	// Check if the file could be opened
	if (!i.good()) 
	{
		std::string errorMessage = "Could not open file: " + m_dataPath + "Levels/" + fileName + ".json";
		if (i.fail()) 
		{
			errorMessage += " (file does not exist or cannot be opened)";
		}
		throw std::runtime_error(errorMessage);
	}
	nlohmann::json j;
	i >> j;

	// Process player
	auto player = std::make_unique<dae::GameObject>("Player");
	std::unique_ptr<GameObject> player2 = nullptr;
	player->AddComponent<dae::TextureComponent>()->SetTexture(resources.LoadTexture("Peter.png"));
	player->AddComponent<dae::PlayerComponent>();
	auto playerLives = player->AddComponent<dae::LivesComponent>();
	auto playerScore = player->AddComponent<dae::ScoreComponent>();
	player->SetLocalPosition({ j["Player"]["Position"]["x"], j["Player"]["Position"]["y"], 0 });
	auto playerTexture = player->GetComponent<dae::TextureComponent>();
	player->GetTransform().SetDimensions(playerTexture->GetDimensions());

	// Add player1 lives observer object
	auto livesObserver = std::make_unique<dae::GameObject>("Background");
	livesObserver->AddComponent<dae::TextureComponent>();
	livesObserver->GetTransform().SetLocalPosition(32, 32, 0);
	livesObserver->AddComponent<dae::TextComponent>()->SetFont(font);
	livesObserver->AddComponent<dae::LivesObserverComponent>();
	playerLives->AddObserver(livesObserver->GetComponent<dae::LivesObserverComponent>());

	// Add player1 lives observer object
	auto scoreObserver = std::make_unique<dae::GameObject>("Background");
	scoreObserver->AddComponent<dae::TextureComponent>();
	scoreObserver->GetTransform().SetLocalPosition(480 - 128, 32, 0);
	scoreObserver->AddComponent<dae::TextComponent>()->SetFont(font);
	scoreObserver->AddComponent<dae::ScoreObserverComponent>();
	playerScore->AddObserver(scoreObserver->GetComponent<dae::ScoreObserverComponent>());

	// Process level layout
	for (const auto& layout : j["Layout"])
	{
		// Process ladders
		if (layout["Type"] == "Ladder")
		{
			// Create a new GameObject
			auto ladder = std::make_unique<dae::GameObject>("Ladder");

			// Add a TextureComponent to the GameObject
			auto texture = ladder->AddComponent<dae::TextureComponent>();

			// Set the texture of the TextureComponent
			if (layout["Length"] == "1")
			{
				texture->SetTexture(resources.LoadTexture("Ladder1.png"));
			}
			else if (layout["Length"] == "2")
			{
				texture->SetTexture(resources.LoadTexture("Ladder2.png"));
			}
			else if (layout["Length"] == "3")
			{
				texture->SetTexture(resources.LoadTexture("Ladder3.png"));
			}
			else if (layout["Length"] == "4")
			{
				texture->SetTexture(resources.LoadTexture("Ladder4.png"));
			}
			else
			{
				throw std::runtime_error("Invalid ladder length");
			}

			// Set the position of the GameObject
			ladder->SetLocalPosition({ layout["Position"]["x"], layout["Position"]["y"], 0 });

			// Set the scale of the TextureComponent
			auto ladderTexture = ladder->GetComponent<dae::TextureComponent>();
			// Set the dimensions of the TransformComponent
			ladder->GetTransform().SetDimensions(ladderTexture->GetDimensions());

			gameObjects.push_back(std::move(ladder));
		}

		// Process platforms
		else if (layout["Type"] == "Platform")
		{
			// Create a new GameObject
			auto platform = std::make_unique<dae::GameObject>("Platform");
			
			// Add a TextureComponent to the GameObject
			auto texture = platform->AddComponent<dae::TextureComponent>();

			// Set the texture of the TextureComponent
			if (layout["Length"] == "1")
			{
				texture->SetTexture(resources.LoadTexture("Platform1.png"));
			}
			else if (layout["Length"] == "2")
			{
				texture->SetTexture(resources.LoadTexture("Platform2.png"));
			}
			else if (layout["Length"] == "3")
			{
				texture->SetTexture(resources.LoadTexture("Platform3.png"));
			}
			else if (layout["Length"] == "4")
			{
				texture->SetTexture(resources.LoadTexture("Platform4.png"));
			}
			else
			{
				throw std::runtime_error("Invalid platform length");
			}

			platform->AddComponent<dae::PlatformComponent>();
			// Set the position of the GameObject
			platform->SetLocalPosition({ layout["Position"]["x"], layout["Position"]["y"], 0 });

			// Set the scale of the TextureComponent
			auto platformTexture = platform->GetComponent<dae::TextureComponent>();
			// Set the dimensions of the TransformComponent
			platform->GetTransform().SetDimensions(platformTexture->GetDimensions());

			gameObjects.push_back(std::move(platform));
		}

		// Process ingredients
		else if (layout["Type"] == "Ingredient")
		{
			// Set the texture of the TextureComponent
			if (layout["Option"] == "1")
			{
				auto temp = CreateIngredient("BunTop", layout["Position"]["x"], layout["Position"]["y"], layout["Id"]);
				for (auto& ingredientPart : temp)
				{
					gameObjects.push_back(std::move(ingredientPart));
				}
			}
			else if (layout["Option"] == "2")
			{
				auto temp = CreateIngredient("Patty", layout["Position"]["x"], layout["Position"]["y"], layout["Id"]);
				for (auto& ingredientPart : temp)
				{
					gameObjects.push_back(std::move(ingredientPart));
				}
			}
			else if (layout["Option"] == "3")
			{
				auto temp = CreateIngredient("Cheese", layout["Position"]["x"], layout["Position"]["y"], layout["Id"]);
				for (auto& ingredientPart : temp)
				{
					gameObjects.push_back(std::move(ingredientPart));
				}
			}
			else if (layout["Option"] == "4")
			{
				auto temp = CreateIngredient("Lettuce", layout["Position"]["x"], layout["Position"]["y"], layout["Id"]);
				for (auto& ingredientPart : temp)
				{
					gameObjects.push_back(std::move(ingredientPart));
				}
			}
			else if (layout["Option"] == "5")
			{
				auto temp = CreateIngredient("Tomato", layout["Position"]["x"], layout["Position"]["y"], layout["Id"]);
				for (auto& ingredientPart : temp)
				{
					gameObjects.push_back(std::move(ingredientPart));
				}
			}
			else if (layout["Option"] == "6")
			{
				auto temp = CreateIngredient("BunBottom", layout["Position"]["x"], layout["Position"]["y"], layout["Id"]);
				for (auto& ingredientPart : temp)
				{
					gameObjects.push_back(std::move(ingredientPart));
				}
			}
			else
			{
				throw std::runtime_error("Unknown ingredient option");
			}
		}
		else if (layout["Type"] == "Plate")
		{
			// Create a new GameObject
			auto plate = std::make_unique<dae::GameObject>("Plate");

			// Add a TextureComponent to the GameObject
			auto texture = plate->AddComponent<dae::TextureComponent>();

			// Add a PlateComponent to the GameObject
			plate->AddComponent<dae::PlateComponent>();

			// Set the texture of the TextureComponent
			texture->SetTexture(resources.LoadTexture("Plate.png"));

			// Set the position of the GameObject
			plate->SetLocalPosition({ layout["Position"]["x"], layout["Position"]["y"], 0 });

			// Set the dimensions of the TransformComponent
			plate->GetTransform().SetDimensions(texture->GetDimensions());

			gameObjects.push_back(std::move(plate));
		}
		else
		{
			throw std::runtime_error("Unknown layout type");
		}
    }

	// Process each EnemyType
	for (const auto& enemy : j["Enemies"])
	{
		// Create a new GameObject
		auto enemyObj = std::make_unique<dae::GameObject>("Enemy");
		enemyObj->SetLocalPosition({ enemy["Position"]["x"], enemy["Position"]["y"], 0 });

		if (enemy["Type"] == "Hotdog")
		{
			enemyObj->AddComponent<dae::EnemyComponent>()->SetType(EnemyType::Hotdog);
			enemyObj->AddComponent<dae::TextureComponent>()->SetTexture(resources.LoadTexture("HotdogWalk.png"));
		}
		else if (enemy["Type"] == "Egg")
		{
			enemyObj->AddComponent<dae::EnemyComponent>()->SetType(EnemyType::Egg);
			enemyObj->AddComponent<dae::TextureComponent>()->SetTexture(resources.LoadTexture("EggWalk.png"));
		}
		else if (enemy["Type"] == "Pickle")
		{
			enemyObj->AddComponent<dae::EnemyComponent>()->SetType(EnemyType::Pickle);
			enemyObj->AddComponent<dae::TextureComponent>()->SetTexture(resources.LoadTexture("PickleWalk.png"));
		}
		else
		{
			throw std::runtime_error("Unknown enemy type");
		}

		gameObjects.push_back(std::move(enemyObj));
	}

	// If the scene does not exist, create it
	if (!sceneManager.HasScene(sceneName))
	{
		sceneManager.CreateScene(sceneName);
	}

	// Get scene
	auto& scene = sceneManager.GetScene(sceneName);

	// Add Player commands
	auto& input = dae::InputManager::GetInstance();
	float playerSpeed = 100.f;

	// Singleplayer
	if (sceneName != "Multiplayer" && sceneName != "Versus")
	{
		// Controller
		{
			// Start Move
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadUp, dae::keyState::isDown, std::make_unique<dae::ClimbStartCommand>(player.get(), -playerSpeed));
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadDown, dae::keyState::isDown, std::make_unique<dae::ClimbStartCommand>(player.get(), playerSpeed));
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadLeft, dae::keyState::isDown, std::make_unique<dae::WalkStartCommand>(player.get(), -playerSpeed));
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadRight, dae::keyState::isDown, std::make_unique<dae::WalkStartCommand>(player.get(), playerSpeed));
		}
		{
			// Move
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadUp, dae::keyState::isHeld, std::make_unique<dae::ClimbCommand>(player.get(), -playerSpeed));
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadDown, dae::keyState::isHeld, std::make_unique<dae::ClimbCommand>(player.get(), playerSpeed));
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadLeft, dae::keyState::isHeld, std::make_unique<dae::WalkCommand>(player.get(), -playerSpeed));
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadRight, dae::keyState::isHeld, std::make_unique<dae::WalkCommand>(player.get(), playerSpeed));
		}
		{
			// End Move
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadUp, dae::keyState::isUp, std::make_unique<dae::ClimbEndCommand>(player.get()));
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadDown, dae::keyState::isUp, std::make_unique<dae::ClimbEndCommand>(player.get()));
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadLeft, dae::keyState::isUp, std::make_unique<dae::WalkEndCommand>(player.get()));
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadRight, dae::keyState::isUp, std::make_unique<dae::WalkEndCommand>(player.get()));
		}
		{
			// Throw Pepper
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::ButtonA, dae::keyState::isUp, std::make_unique<dae::ThrowPepperCommand>(player.get()));
		}
	}
	// Multiplayer or Versus
	else
	{
		// Make second player object
		if (sceneName == "Multiplayer")
		{
			player2 = std::make_unique<dae::GameObject>("Player");
			player2->AddComponent<dae::TextureComponent>()->SetTexture(resources.LoadTexture("Peter.png"));
			player2->AddComponent<dae::PlayerComponent>();
			player2->AddComponent<dae::LivesComponent>();
		}
		else if (sceneName == "Versus")
		{
			player2 = std::make_unique<dae::GameObject>("Enemy");
			player2->AddComponent<dae::TextureComponent>()->SetTexture(resources.LoadTexture("HotdogWalk.png"));
			auto enemyComp = player2->AddComponent<dae::EnemyComponent>();
			enemyComp->SetControlled(true);
		}
		player2->SetLocalPosition({ j["Player2"]["Position"]["x"], j["Player2"]["Position"]["y"], 0 });
		auto player2Texture = player2->GetComponent<dae::TextureComponent>();
		player2->GetTransform().SetDimensions(player2Texture->GetDimensions());

		// Controllers
		// Controller 1 controls Player 2
		{
			// Start Move
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadUp, dae::keyState::isDown, std::make_unique<dae::ClimbStartCommand>(player2.get(), -playerSpeed));
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadDown, dae::keyState::isDown, std::make_unique<dae::ClimbStartCommand>(player2.get(), playerSpeed));
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadLeft, dae::keyState::isDown, std::make_unique<dae::WalkStartCommand>(player2.get(), -playerSpeed));
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadRight, dae::keyState::isDown, std::make_unique<dae::WalkStartCommand>(player2.get(), playerSpeed));
			// Do the same but for keyboard
			/*input.AddCommand(sceneName, SDL_SCANCODE_UP, dae::keyState::isDown, std::make_unique<dae::ClimbStartCommand>(player2.get(), -playerSpeed));
			input.AddCommand(sceneName, SDL_SCANCODE_DOWN, dae::keyState::isDown, std::make_unique<dae::ClimbStartCommand>(player2.get(), playerSpeed));
			input.AddCommand(sceneName, SDL_SCANCODE_LEFT, dae::keyState::isDown, std::make_unique<dae::WalkStartCommand>(player2.get(), -playerSpeed));
			input.AddCommand(sceneName, SDL_SCANCODE_RIGHT, dae::keyState::isDown, std::make_unique<dae::WalkStartCommand>(player2.get(), playerSpeed));*/
		}
		{
			// Move
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadUp, dae::keyState::isHeld, std::make_unique<dae::ClimbCommand>(player2.get(), -playerSpeed));
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadDown, dae::keyState::isHeld, std::make_unique<dae::ClimbCommand>(player2.get(), playerSpeed));
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadLeft, dae::keyState::isHeld, std::make_unique<dae::WalkCommand>(player2.get(), -playerSpeed));
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadRight, dae::keyState::isHeld, std::make_unique<dae::WalkCommand>(player2.get(), playerSpeed));
			// Do the same but for keyboard
			/*input.AddCommand(sceneName, SDL_SCANCODE_UP, dae::keyState::isHeld, std::make_unique<dae::ClimbCommand>(player2.get(), -playerSpeed));
			input.AddCommand(sceneName, SDL_SCANCODE_DOWN, dae::keyState::isHeld, std::make_unique<dae::ClimbCommand>(player2.get(), playerSpeed));
			input.AddCommand(sceneName, SDL_SCANCODE_LEFT, dae::keyState::isHeld, std::make_unique<dae::WalkCommand>(player2.get(), -playerSpeed));
			input.AddCommand(sceneName, SDL_SCANCODE_RIGHT, dae::keyState::isHeld, std::make_unique<dae::WalkCommand>(player2.get(), playerSpeed));*/
		}
		{
			// End Move
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadUp, dae::keyState::isUp, std::make_unique<dae::ClimbEndCommand>(player2.get()));
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadDown, dae::keyState::isUp, std::make_unique<dae::ClimbEndCommand>(player2.get()));
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadLeft, dae::keyState::isUp, std::make_unique<dae::WalkEndCommand>(player2.get()));
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadRight, dae::keyState::isUp, std::make_unique<dae::WalkEndCommand>(player2.get()));
			// Do the same but for keyboard
			/*input.AddCommand(sceneName, SDL_SCANCODE_UP, dae::keyState::isUp, std::make_unique<dae::ClimbEndCommand>(player2.get()));
			input.AddCommand(sceneName, SDL_SCANCODE_DOWN, dae::keyState::isUp, std::make_unique<dae::ClimbEndCommand>(player2.get()));
			input.AddCommand(sceneName, SDL_SCANCODE_LEFT, dae::keyState::isUp, std::make_unique<dae::WalkEndCommand>(player2.get()));
			input.AddCommand(sceneName, SDL_SCANCODE_RIGHT, dae::keyState::isUp, std::make_unique<dae::WalkEndCommand>(player2.get()));*/
		}
		if (sceneName == "Multiplayer")
		{
			// Throw Pepper
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::ButtonA, dae::keyState::isUp, std::make_unique<dae::ThrowPepperCommand>(player2.get()));
		}

		// Controller 2 controls Player 1
		// Controller
		{
			// Start Move
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::Second), dae::Controller::ControllerButton::DPadUp, dae::keyState::isDown, std::make_unique<dae::ClimbStartCommand>(player.get(), -playerSpeed));
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::Second), dae::Controller::ControllerButton::DPadDown, dae::keyState::isDown, std::make_unique<dae::ClimbStartCommand>(player.get(), playerSpeed));
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::Second), dae::Controller::ControllerButton::DPadLeft, dae::keyState::isDown, std::make_unique<dae::WalkStartCommand>(player.get(), -playerSpeed));
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::Second), dae::Controller::ControllerButton::DPadRight, dae::keyState::isDown, std::make_unique<dae::WalkStartCommand>(player.get(), playerSpeed));
		}
		{
			// Move
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::Second), dae::Controller::ControllerButton::DPadUp, dae::keyState::isHeld, std::make_unique<dae::ClimbCommand>(player.get(), -playerSpeed));
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::Second), dae::Controller::ControllerButton::DPadDown, dae::keyState::isHeld, std::make_unique<dae::ClimbCommand>(player.get(), playerSpeed));
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::Second), dae::Controller::ControllerButton::DPadLeft, dae::keyState::isHeld, std::make_unique<dae::WalkCommand>(player.get(), -playerSpeed));
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::Second), dae::Controller::ControllerButton::DPadRight, dae::keyState::isHeld, std::make_unique<dae::WalkCommand>(player.get(), playerSpeed));
		}
		{
			// End Move
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::Second), dae::Controller::ControllerButton::DPadUp, dae::keyState::isUp, std::make_unique<dae::ClimbEndCommand>(player.get()));
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::Second), dae::Controller::ControllerButton::DPadDown, dae::keyState::isUp, std::make_unique<dae::ClimbEndCommand>(player.get()));
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::Second), dae::Controller::ControllerButton::DPadLeft, dae::keyState::isUp, std::make_unique<dae::WalkEndCommand>(player.get()));
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::Second), dae::Controller::ControllerButton::DPadRight, dae::keyState::isUp, std::make_unique<dae::WalkEndCommand>(player.get()));
		}
		{
			// Throw Pepper
			input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::Second), dae::Controller::ControllerButton::ButtonA, dae::keyState::isUp, std::make_unique<dae::ThrowPepperCommand>(player.get()));
		}
	}
	// Always
	// Keyboard
	{
		// Start Move
		input.AddCommand(sceneName, SDL_SCANCODE_W, dae::keyState::isDown, std::make_unique<dae::ClimbStartCommand>(player.get(), -playerSpeed));
		input.AddCommand(sceneName, SDL_SCANCODE_S, dae::keyState::isDown, std::make_unique<dae::ClimbStartCommand>(player.get(), playerSpeed));
		input.AddCommand(sceneName, SDL_SCANCODE_A, dae::keyState::isDown, std::make_unique<dae::WalkStartCommand>(player.get(), -playerSpeed));
		input.AddCommand(sceneName, SDL_SCANCODE_D, dae::keyState::isDown, std::make_unique<dae::WalkStartCommand>(player.get(), playerSpeed));
	}
	{
		// Move
		input.AddCommand(sceneName, SDL_SCANCODE_W, dae::keyState::isHeld, std::make_unique<dae::ClimbCommand>(player.get(), -playerSpeed));
		input.AddCommand(sceneName, SDL_SCANCODE_S, dae::keyState::isHeld, std::make_unique<dae::ClimbCommand>(player.get(), playerSpeed));
		input.AddCommand(sceneName, SDL_SCANCODE_A, dae::keyState::isHeld, std::make_unique<dae::WalkCommand>(player.get(), -playerSpeed));
		input.AddCommand(sceneName, SDL_SCANCODE_D, dae::keyState::isHeld, std::make_unique<dae::WalkCommand>(player.get(), playerSpeed));
	}
	{
		// End Move
		input.AddCommand(sceneName, SDL_SCANCODE_W, dae::keyState::isUp, std::make_unique<dae::ClimbEndCommand>(player.get()));
		input.AddCommand(sceneName, SDL_SCANCODE_S, dae::keyState::isUp, std::make_unique<dae::ClimbEndCommand>(player.get()));
		input.AddCommand(sceneName, SDL_SCANCODE_A, dae::keyState::isUp, std::make_unique<dae::WalkEndCommand>(player.get()));
		input.AddCommand(sceneName, SDL_SCANCODE_D, dae::keyState::isUp, std::make_unique<dae::WalkEndCommand>(player.get()));
	}
	{
		// Throw Pepper
		input.AddCommand(sceneName, SDL_SCANCODE_SPACE, dae::keyState::isDown, std::make_unique<dae::ThrowPepperCommand>(player.get()));
	}

	for (auto& obj : gameObjects)
	{
		// Scale if obj has a TextureComponent
		if (obj->HasComponent<dae::TextureComponent>())
		{
			// Scale if not scaled yet
			auto textureComp = obj->GetComponent<dae::TextureComponent>();
			if (textureComp->GetScale() == 1)
			{
				textureComp->SetScale(2);
			}
		}
		scene.Add(std::move(obj));
	}

	// Scale if player has a TextureComponent
	if (player->HasComponent<dae::TextureComponent>())
	{
		player->GetComponent<dae::TextureComponent>()->SetScale(2);
	}

	if (player2)
	{
		// Scale if player has a TextureComponent
		if (player2->HasComponent<dae::TextureComponent>())
		{
			player2->GetComponent<dae::TextureComponent>()->SetScale(2);
		}
		scene.Add(std::move(player2));
	}

	// Add Player last for correct rendering
	scene.Add(std::move(player));

	scene.Add(std::move(livesObserver));
	scene.Add(std::move(scoreObserver));

	RegisterObjects<PlayerComponent>("Player", sceneName);
	RegisterObjects<PlateComponent>("Plate", sceneName);
	RegisterObjects<PlatformComponent>("Platform", sceneName);
	RegisterObjects<IngredientComponent>("Ingredient", sceneName);

#ifndef NDEBUG
	// FPS
	font = resources.LoadFont("Lingua.otf", 36);
	auto go = std::make_unique<dae::GameObject>("Background");
	go->AddComponent<dae::TextureComponent>();
	go->AddComponent<dae::TextComponent>()->SetFont(font);
	go->AddComponent<dae::FPSComponent>();
	scene.Add(std::move(go));
#endif
}

std::vector<std::unique_ptr<dae::GameObject>> dae::LevelLoader::CreateIngredient(std::string type, float x, float y, int id)
{
	std::vector<std::unique_ptr<dae::GameObject>> gameObjects{};

	// Create bun left side
	auto& resources = dae::ResourceManager::GetInstance();
	auto sideTexture = resources.LoadTexture(type + "Side.png");
	auto middleTexture = resources.LoadTexture(type + "Middle.png");

	// Create 4 parts of the ingredient
	for (int i{}; i < 4; ++i)
	{
		// Create a new GameObject on position x, y
		auto ingredient = std::make_unique<dae::GameObject>("Ingredient");
		ingredient->SetLocalPosition({ x, y, 0 });
		// Give temporary texture and scale for maths
		auto texture = ingredient->AddComponent<dae::TextureComponent>();
		ingredient->GetComponent<dae::TextureComponent>()->SetTexture(sideTexture);
		texture->SetScale(2);
		// Set up the ingredient component
		auto ingredientComp = ingredient->AddComponent<dae::IngredientComponent>();
		ingredientComp->SetType(type);
		ingredientComp->SetId(id);
		// Put it in the vector
		gameObjects.push_back(std::move(ingredient));

		// Move x to the right
		x += texture->GetDimensions().x;
	}

	// Set correct textures (and scale) for each part
	auto texture = gameObjects[0]->GetComponent<dae::TextureComponent>();
	texture->SetTexture(sideTexture);

	texture = gameObjects[1]->GetComponent<dae::TextureComponent>();
	texture->SetTexture(middleTexture);

	texture = gameObjects[2]->GetComponent<dae::TextureComponent>();
	texture->SetTexture(middleTexture);
	texture->SetScale(-2);

	texture = gameObjects[3]->GetComponent<dae::TextureComponent>();
	texture->SetTexture(sideTexture);
	texture->SetScale(-2);

	return gameObjects;
}
