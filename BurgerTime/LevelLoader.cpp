#include "LevelLoader.h"
#include "GameObject.h"
#include <TextureComponent.h>
#include <ResourceManager.h>
#include "PlatformComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include <fstream>
#include "json.hpp" // nlohmann::json
#include "PlayerComponent.h"
#include <InputManager.h>
#include "GameCommands.h"
#include <memory>
#include "HotdogComponent.h"
#include "EggComponent.h"
#include "PickleComponent.h"
//#include <SpriteComponent.h>

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
	//player->AddComponent<dae::SpriteComponent>("Player.png");
	player->AddComponent<dae::TextureComponent>()->SetTexture(resources.LoadTexture("Peter.png"));
	player->AddComponent<dae::PlayerComponent>();
	player->SetLocalPosition({ j["Player"]["Position"]["x"], j["Player"]["Position"]["y"], 0 });
	auto playerTexture = player->GetComponent<dae::TextureComponent>();
	player->GetTransform().SetDimensions(playerTexture->GetDimensions());

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
			// Create a new GameObject
			auto ingredient = std::make_unique<dae::GameObject>("Ingredient");

			// Add a TextureComponent to the GameObject
			auto texture = ingredient->AddComponent<dae::TextureComponent>();

			// Set the texture of the TextureComponent
			if (layout["Option"] == "1")
			{
				texture->SetTexture(resources.LoadTexture("Ingredient1.png"));
			}
			else if (layout["Option"] == "2")
			{
				texture->SetTexture(resources.LoadTexture("Ingredient2.png"));
			}
			else if (layout["Option"] == "3")
			{
				texture->SetTexture(resources.LoadTexture("Ingredient3.png"));
			}
			else if (layout["Option"] == "4")
			{
				texture->SetTexture(resources.LoadTexture("Ingredient4.png"));
			}
			else if (layout["Option"] == "5")
			{
				texture->SetTexture(resources.LoadTexture("Ingredient5.png"));
			}
			else if (layout["Option"] == "6")
			{
				texture->SetTexture(resources.LoadTexture("Ingredient6.png"));
			}
			else
			{
				throw std::runtime_error("Unknown ingredient option");
			}

			// Set the position of the GameObject
			ingredient->SetLocalPosition({ layout["Position"]["x"], layout["Position"]["y"], 0 });

			// Set the scale of the TextureComponent
			auto ingredientTexture = ingredient->GetComponent<dae::TextureComponent>();
			// Set the dimensions of the TransformComponent
			ingredient->GetTransform().SetDimensions(ingredientTexture->GetDimensions());

			gameObjects.push_back(std::move(ingredient));
		}

		else
		{
			throw std::runtime_error("Unknown layout type");
		}
    }

	// Process each EnemyType
	for (const auto& enemy : j["Enemies"])
	{
		// Process Hotdogs
		if (enemy["Type"] == "Hotdog")
		{
			auto hotdog = std::make_unique<dae::GameObject>("Enemy");
			//hotdog->AddComponent<dae::SpriteComponent>("HotdogWalk.png");
			hotdog->AddComponent<dae::TextureComponent>()->SetTexture(resources.LoadTexture("HotdogWalk.png"));
			hotdog->AddComponent<dae::HotdogComponent>();
			hotdog->SetLocalPosition({ enemy["Position"]["x"], enemy["Position"]["y"], 0 });

			gameObjects.push_back(std::move(hotdog));
		}

		// Process Eggs
		else if (enemy["Type"] == "Egg")
		{
			auto egg = std::make_unique<dae::GameObject>("Enemy");
			//egg->AddComponent<dae::SpriteComponent>("EggWalk.png");
			egg->AddComponent<dae::TextureComponent>()->SetTexture(resources.LoadTexture("EggWalk.png"));
			egg->AddComponent<dae::EggComponent>();
			egg->SetLocalPosition({ enemy["Position"]["x"], enemy["Position"]["y"], 0 });

			gameObjects.push_back(std::move(egg));
		}

		// Process Pickles
		else if (enemy["Type"] == "Pickle")
		{
			auto pickle = std::make_unique<dae::GameObject>("Enemy");
			//pickle->AddComponent<dae::SpriteComponent>("PickleWalk.png");
			pickle->AddComponent<dae::TextureComponent>()->SetTexture(resources.LoadTexture("PickleWalk.png"));
			pickle->AddComponent<dae::PickleComponent>();
			pickle->SetLocalPosition({ enemy["Position"]["x"], enemy["Position"]["y"], 0 });

			gameObjects.push_back(std::move(pickle));
		}

		else
		{
			throw std::runtime_error("Unknown enemy type");
		}
	}

	// If the scene does not exist, create it
	if (!sceneManager.HasScene(sceneName))
	{
		sceneManager.CreateScene(sceneName);
	}

	// Add Player commands
	auto& input = dae::InputManager::GetInstance();

	// Controller
	{
		// Start Move
		input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadUp, dae::keyState::isUp, std::make_unique<dae::ClimbStartCommand>(player.get(), -50.f));
		input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadDown, dae::keyState::isUp, std::make_unique<dae::ClimbStartCommand>(player.get(), 50.f));
		input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadLeft, dae::keyState::isUp, std::make_unique<dae::WalkStartCommand>(player.get(), -50.f));
		input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadRight, dae::keyState::isUp, std::make_unique<dae::WalkStartCommand>(player.get(), 50.f));
	}
	{
		// Move
		input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadUp, dae::keyState::isUp, std::make_unique<dae::ClimbCommand>(player.get(), -50.f));
		input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadDown, dae::keyState::isUp, std::make_unique<dae::ClimbCommand>(player.get(), 50.f));
		input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadLeft, dae::keyState::isUp, std::make_unique<dae::WalkCommand>(player.get(), -50.f));
		input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadRight, dae::keyState::isUp, std::make_unique<dae::WalkCommand>(player.get(), 50.f));
	}
	{
		// End Move
		input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadUp, dae::keyState::isUp, std::make_unique<dae::ClimbEndCommand>(player.get()));
		input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadDown, dae::keyState::isUp, std::make_unique<dae::ClimbEndCommand>(player.get()));
		input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadLeft, dae::keyState::isUp, std::make_unique<dae::WalkEndCommand>(player.get()));
		input.AddCommand(sceneName, static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadRight, dae::keyState::isUp, std::make_unique<dae::WalkEndCommand>(player.get()));
	}
	
	// Keyboard
	{
		// Start Move
		input.AddCommand(sceneName, SDL_SCANCODE_W, dae::keyState::isDown, std::make_unique<dae::ClimbStartCommand>(player.get(), -50.f));
		input.AddCommand(sceneName, SDL_SCANCODE_S, dae::keyState::isDown, std::make_unique<dae::ClimbStartCommand>(player.get(), 50.f));
		input.AddCommand(sceneName, SDL_SCANCODE_A, dae::keyState::isDown, std::make_unique<dae::WalkStartCommand>(player.get(), -50.f));
		input.AddCommand(sceneName, SDL_SCANCODE_D, dae::keyState::isDown, std::make_unique<dae::WalkStartCommand>(player.get(), 50.f));
	}
	{
		// Move
		input.AddCommand(sceneName, SDL_SCANCODE_W, dae::keyState::isHeld, std::make_unique<dae::ClimbCommand>(player.get(), -50.f));
		input.AddCommand(sceneName, SDL_SCANCODE_S, dae::keyState::isHeld, std::make_unique<dae::ClimbCommand>(player.get(), 50.f));
		input.AddCommand(sceneName, SDL_SCANCODE_A, dae::keyState::isHeld, std::make_unique<dae::WalkCommand>(player.get(), -50.f));
		input.AddCommand(sceneName, SDL_SCANCODE_D, dae::keyState::isHeld, std::make_unique<dae::WalkCommand>(player.get(), 50.f));
	}
	{
		// End Move
		input.AddCommand(sceneName, SDL_SCANCODE_W, dae::keyState::isUp, std::make_unique<dae::ClimbEndCommand>(player.get()));
		input.AddCommand(sceneName, SDL_SCANCODE_S, dae::keyState::isUp, std::make_unique<dae::ClimbEndCommand>(player.get()));
		input.AddCommand(sceneName, SDL_SCANCODE_A, dae::keyState::isUp, std::make_unique<dae::WalkEndCommand>(player.get()));
		input.AddCommand(sceneName, SDL_SCANCODE_D, dae::keyState::isUp, std::make_unique<dae::WalkEndCommand>(player.get()));
	}

	// Add the GameObjects to the scene
	auto& scene = sceneManager.GetScene(sceneName);

	for (auto& obj : gameObjects)
	{
		// Scale if obj has a TextureComponent
		if (obj->HasComponent<dae::TextureComponent>())
		{
			obj->GetComponent<dae::TextureComponent>()->SetScale(2);
		}
		scene.Add(std::move(obj));
	}

	// Scale if player has a TextureComponent
	if (player->HasComponent<dae::TextureComponent>())
	{
		player->GetComponent<dae::TextureComponent>()->SetScale(2);
	}
	// Add Player last for correct rendering
	scene.Add(std::move(player));

	// Get all Platform Objects
	auto platforms = scene.GetObjectsByTag("Platform");
	// Register all objects to PlatformComponent
	for (auto& platform : platforms)
	{
		platform->GetComponent<dae::PlatformComponent>()->RegisterObjects();
	}
}
