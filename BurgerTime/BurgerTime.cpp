#pragma once
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <Minigin.h>
#include <SDL_mixer.h>
#include <SDL.h>

#include <SoundServiceLocator.h>
#include <LoggingSoundSystem.h>
#include <NullSoundSystem.h>
#include <ResourceManager.h>
#include <SDLSoundSystem.h>
#include <SceneManager.h>
#include <InputManager.h>
#include <Scene.h>
#include "LevelLoader.h"

// Components
#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "RotationComponent.h"
#include "LivesObserverComponent.h"
#include "LivesComponent.h"
#include "ScoreObserverComponent.h"
#include "ScoreComponent.h"
#include "PlayerComponent.h"
#include "PlatformComponent.h"

#include "GameObject.h"
#include "Controller.h"
#include "Command.h"
#include "GameCommands.h"

void load()
{
#if NDEBUG
	dae::SoundServiceLocator::RegisterSoundSystem(std::make_unique<dae::SDLSoundSystem>());
#else
	dae::SoundServiceLocator::RegisterSoundSystem(
		std::make_unique<dae::LoggingSoundSystem>(std::make_unique<dae::NullSoundSystem>())
	);
#endif

	// Managers
	auto& sceneManager = dae::SceneManager::GetInstance();
	auto& soundSystem = dae::SoundServiceLocator::GetSoundSystem();
	auto& resourceManager = dae::ResourceManager::GetInstance();
	auto& input = dae::InputManager::GetInstance();

	// Menu scene
	{
		auto& scene = sceneManager.CreateScene("Menu");

		soundSystem.StopMusic();

		// Add controllers
		input.AddControllersMax();

		// Background
		auto go = std::make_unique<dae::GameObject>("Background");
		go->AddComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("background.tga"));
		scene.Add(std::move(go));

		// Logo
		go = std::make_unique<dae::GameObject>("Background");
		go->AddComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("logo.tga"));
		go->GetTransform().SetWorldPosition(216, 180, 0);
		scene.Add(std::move(go));

		// Text
		auto font = resourceManager.LoadFont("Lingua.otf", 36);
		go = std::make_unique<dae::GameObject>("Background");
		go->AddComponent<dae::TextureComponent>();
		go->AddComponent<dae::TextComponent>()->SetFont(font);
		go->GetComponent<dae::TextComponent>()->SetText("Press \"SPACE\" To Start!");
		go->GetTransform().SetWorldPosition(80, 20, 0);
		scene.Add(std::move(go));

		// FPS
		go = std::make_unique<dae::GameObject>("Background");
		go->AddComponent<dae::TextureComponent>();
		go->AddComponent<dae::TextComponent>()->SetFont(font);
		go->AddComponent<dae::FPSComponent>();
		scene.Add(std::move(go));

		input.AddCommand("Menu", SDL_SCANCODE_SPACE, dae::keyState::isDown, std::make_unique<dae::SceneSwapCommand>("Level1", "../Data/Soundtrack.mp3"));
	}

	// Demo scene
	/*{
		auto& scene = sceneManager.CreateScene("Demo");

		// Load and Play Sound
		dae::Sound temp{ "../Data/Soundtrack.mp3", "Soundtrack", -1 };
		soundSystem.PlayMusic(temp);
		//soundSystem.StopMusic();

		// Controllers
		input.AddControllersMax();

		// Background
		auto go = std::make_unique<dae::GameObject>("Background");
		go->AddComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("background.tga"));
		scene.Add(std::move(go));

		// Logo
		go = std::make_unique<dae::GameObject>("Background");
		go->AddComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("logo.tga"));
		go->GetTransform().SetWorldPosition(216, 180, 0);
		scene.Add(std::move(go));

		// Text
		auto font = resourceManager.LoadFont("Lingua.otf", 36);
		go = std::make_unique<dae::GameObject>("Background");
		go->AddComponent<dae::TextureComponent>();
		go->AddComponent<dae::TextComponent>()->SetFont(font);
		go->GetComponent<dae::TextComponent>()->SetText("Programming 4 Assignment");
		go->GetTransform().SetWorldPosition(80, 20, 0);
		scene.Add(std::move(go));

		// FPS
		go = std::make_unique<dae::GameObject>("Background");
		go->AddComponent<dae::TextureComponent>();
		go->AddComponent<dae::TextComponent>()->SetFont(font);
		go->AddComponent<dae::FPSComponent>();
		scene.Add(std::move(go));

		// Pivot point
		//go = std::make_unique<dae::GameObject>();
		//go->GetTransform().SetWorldPosition(310, 300, 0);
		//scene.Add(std::move(go));

		// Chef
		auto goc = std::make_unique<dae::GameObject>("Player");
		goc->AddComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("Peter.png"));
		goc->GetTransform().SetLocalPosition(50, 0, 0);
		//goc->AddComponent<dae::RotationComponent>();

		// Hotdog
		auto gob = std::make_unique<dae::GameObject>("Player");
		//gob->SetParent(goc.get(), false);
		gob->AddComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("HotdogWalk.png"));
		gob->GetTransform().SetLocalPosition(75, 0, 0);
		//gob->AddComponent<dae::RotationComponent>();
		//gob->GetComponent<dae::RotationComponent>()->SetRotationSpeed(360.f);
		


		// Climbing test obj
		auto ladderObj = std::make_unique<dae::GameObject>("Ladder");
		ladderObj->AddComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("platform1.png"));
		ladderObj->GetTransform().SetWorldPosition(50, 200, 0);
		if (ladderObj->HasComponent<dae::TextureComponent>())
		{
			auto platformTexture = ladderObj->GetComponent<dae::TextureComponent>();
			platformTexture->SetScale(1);
			ladderObj->GetTransform().SetDimensions(platformTexture->GetDimensions());
			ladderObj->GetTransform().SetHeight(1000);
		}
		scene.Add(std::move(ladderObj));


		// Collision obj
		auto staticObj = std::make_unique<dae::GameObject>("Platform");
		staticObj->AddComponent<dae::PlatformComponent>();
		staticObj->AddComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("platform1.png"));
		staticObj->GetTransform().SetWorldPosition(50, 200, 0);
		if (staticObj->HasComponent<dae::TextureComponent>())
		{
			auto platformTexture = staticObj->GetComponent<dae::TextureComponent>();
			platformTexture->SetScale(1);
			staticObj->GetTransform().SetDimensions(platformTexture->GetDimensions());
		}

		// Platform obj
		auto platformObj = std::make_unique<dae::GameObject>("Platform");
		platformObj->AddComponent<dae::PlatformComponent>();
		platformObj->AddComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("platform1.png"));
		platformObj->GetTransform().SetWorldPosition(200, 220, 0);
		if (platformObj->HasComponent<dae::TextureComponent>())
		{
			auto platformTexture = platformObj->GetComponent<dae::TextureComponent>();
			platformTexture->SetScale(1);
			platformObj->GetTransform().SetDimensions(platformTexture->GetDimensions());
		}

		// Player Components
		gob->AddComponent<dae::PlayerComponent>();
		if (gob->HasComponent<dae::TextureComponent>())
		{
			auto gobTexture = gob->GetComponent<dae::TextureComponent>();
			gobTexture->SetScale(1);
		}
		goc->AddComponent<dae::PlayerComponent>();
		if (goc->HasComponent<dae::TextureComponent>())
		{
			auto gocTexture = goc->GetComponent<dae::TextureComponent>();
			gocTexture->SetScale(2);
			goc->GetTransform().SetDimensions(gocTexture->GetDimensions());
		}



		// Input
		// Controller
		// Move
		input.AddCommand("Demo", static_cast<int>(dae::Controller::ControllerIdx::Second), dae::Controller::ControllerButton::DPadRight, dae::keyState::isHeld, std::make_unique<dae::WalkCommand>(gob.get(), -200.f));
		input.AddCommand("Demo", static_cast<int>(dae::Controller::ControllerIdx::Second), dae::Controller::ControllerButton::DPadLeft, dae::keyState::isHeld, std::make_unique<dae::WalkCommand>(gob.get(), 200.f));
		input.AddCommand("Demo", static_cast<int>(dae::Controller::ControllerIdx::Second), dae::Controller::ControllerButton::DPadUp, dae::keyState::isHeld, std::make_unique<dae::ClimbCommand>(gob.get(), -200.f));
		input.AddCommand("Demo", static_cast<int>(dae::Controller::ControllerIdx::Second), dae::Controller::ControllerButton::DPadDown, dae::keyState::isHeld, std::make_unique<dae::ClimbCommand>(gob.get(), 200.f));
		// Move
		input.AddCommand("Demo", static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadRight, dae::keyState::isHeld, std::make_unique<dae::WalkCommand>(goc.get(), -400.f));
		input.AddCommand("Demo", static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadLeft, dae::keyState::isHeld, std::make_unique<dae::WalkCommand>(goc.get(), 400.f));
		input.AddCommand("Demo", static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadUp, dae::keyState::isHeld, std::make_unique<dae::ClimbCommand>(goc.get(), -400.f));
		input.AddCommand("Demo", static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadDown, dae::keyState::isHeld, std::make_unique<dae::ClimbCommand>(goc.get(), 400.f));

		// Keyboard
		{
			// Start Move
			input.AddCommand("Demo", SDL_SCANCODE_W, dae::keyState::isDown, std::make_unique<dae::ClimbStartCommand>(gob.get()));
			input.AddCommand("Demo", SDL_SCANCODE_S, dae::keyState::isDown, std::make_unique<dae::ClimbStartCommand>(gob.get()));
			input.AddCommand("Demo", SDL_SCANCODE_A, dae::keyState::isDown, std::make_unique<dae::WalkStartCommand>(gob.get()));
			input.AddCommand("Demo", SDL_SCANCODE_D, dae::keyState::isDown, std::make_unique<dae::WalkStartCommand>(gob.get()));
			// Start Move
			input.AddCommand("Demo", SDL_SCANCODE_UP, dae::keyState::isDown, std::make_unique<dae::ClimbStartCommand>(goc.get()));
			input.AddCommand("Demo", SDL_SCANCODE_DOWN, dae::keyState::isDown, std::make_unique<dae::ClimbStartCommand>(goc.get()));
			input.AddCommand("Demo", SDL_SCANCODE_LEFT, dae::keyState::isDown, std::make_unique<dae::WalkStartCommand>(goc.get()));
			input.AddCommand("Demo", SDL_SCANCODE_RIGHT, dae::keyState::isDown, std::make_unique<dae::WalkStartCommand>(goc.get()));
		}
		{
			// Move
			input.AddCommand("Demo", SDL_SCANCODE_W, dae::keyState::isHeld, std::make_unique<dae::ClimbCommand>(gob.get(), -200.f));
			input.AddCommand("Demo", SDL_SCANCODE_S, dae::keyState::isHeld, std::make_unique<dae::ClimbCommand>(gob.get(), 200.f));
			input.AddCommand("Demo", SDL_SCANCODE_A, dae::keyState::isHeld, std::make_unique<dae::WalkCommand>(gob.get(),-200.f));
			input.AddCommand("Demo", SDL_SCANCODE_D, dae::keyState::isHeld, std::make_unique<dae::WalkCommand>(gob.get(), 200.f));
			// Move
			input.AddCommand("Demo", SDL_SCANCODE_UP, dae::keyState::isHeld, std::make_unique<dae::ClimbCommand>(goc.get(), -400.f));
			input.AddCommand("Demo", SDL_SCANCODE_DOWN, dae::keyState::isHeld, std::make_unique<dae::ClimbCommand>(goc.get(), 400.f));
			input.AddCommand("Demo", SDL_SCANCODE_LEFT, dae::keyState::isHeld, std::make_unique<dae::WalkCommand>(goc.get(), -400.f));
			input.AddCommand("Demo", SDL_SCANCODE_RIGHT, dae::keyState::isHeld, std::make_unique<dae::WalkCommand>(goc.get(), 400.f));
		}
		{
			// End Move
			input.AddCommand("Demo", SDL_SCANCODE_W, dae::keyState::isUp, std::make_unique<dae::ClimbEndCommand>(gob.get()));
			input.AddCommand("Demo", SDL_SCANCODE_S, dae::keyState::isUp, std::make_unique<dae::ClimbEndCommand>(gob.get()));
			input.AddCommand("Demo", SDL_SCANCODE_A, dae::keyState::isUp, std::make_unique<dae::WalkEndCommand>(gob.get()));
			input.AddCommand("Demo", SDL_SCANCODE_D, dae::keyState::isUp, std::make_unique<dae::WalkEndCommand>(gob.get()));
			// End Move
			input.AddCommand("Demo", SDL_SCANCODE_UP, dae::keyState::isUp, std::make_unique<dae::ClimbEndCommand>(goc.get()));
			input.AddCommand("Demo", SDL_SCANCODE_DOWN, dae::keyState::isUp, std::make_unique<dae::ClimbEndCommand>(goc.get()));
			input.AddCommand("Demo", SDL_SCANCODE_LEFT, dae::keyState::isUp, std::make_unique<dae::WalkEndCommand>(goc.get()));
			input.AddCommand("Demo", SDL_SCANCODE_RIGHT, dae::keyState::isUp, std::make_unique<dae::WalkEndCommand>(goc.get()));
		}
		{
			// Kill
			input.AddCommand("Demo", SDL_SCANCODE_Z, dae::keyState::isDown, std::make_unique<dae::KillCommand>(goc.get()));
			input.AddCommand("Demo", SDL_SCANCODE_X, dae::keyState::isDown, std::make_unique<dae::KillCommand>(gob.get()));
			// Score
			input.AddCommand("Demo", SDL_SCANCODE_C, dae::keyState::isDown, std::make_unique<dae::HotdogKilledCommand>(goc.get()));
			input.AddCommand("Demo", SDL_SCANCODE_V, dae::keyState::isDown, std::make_unique<dae::HotdogKilledCommand>(gob.get()));
		}

		// Print Controls
		font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
		go = std::make_unique<dae::GameObject>("Background");
		go->AddComponent<dae::TextureComponent>();
		go->AddComponent<dae::TextComponent>()->SetFont(font);
		go->GetComponent<dae::TextComponent>()->SetText("WASD or DPad to control the Hotdog (Second controller)");
		go->GetTransform().SetWorldPosition(10, 75, 0);
		scene.Add(std::move(go));

		go = std::make_unique<dae::GameObject>("Background");
		go->AddComponent<dae::TextureComponent>();
		go->AddComponent<dae::TextComponent>()->SetFont(font);
		go->GetComponent<dae::TextComponent>()->SetText("Arrows or DPad to control the Chef (First controller)");
		go->GetTransform().SetWorldPosition(10, 100, 0);
		scene.Add(std::move(go));
		
		// Lives Display Chef
		auto toLivesDisplayChef = std::make_unique<dae::GameObject>("Background");
		toLivesDisplayChef->AddComponent<dae::TextureComponent>();
		toLivesDisplayChef->GetTransform().SetLocalPosition(10, 200, 0);
		toLivesDisplayChef->AddComponent<dae::TextComponent>()->SetFont(font);
		toLivesDisplayChef->AddComponent<dae::LivesObserverComponent>();

		// Score Display Chef
		auto toScoreDisplayChef = std::make_unique<dae::GameObject>("Background");
		toScoreDisplayChef->AddComponent<dae::TextureComponent>();
		toScoreDisplayChef->GetTransform().SetLocalPosition(10, 225, 0);
		toScoreDisplayChef->AddComponent<dae::TextComponent>()->SetFont(font);
		toScoreDisplayChef->AddComponent<dae::ScoreObserverComponent>();

		// Lives Display Hotdog
		auto toLivesDisplayHotdog = std::make_unique<dae::GameObject>("Background");
		toLivesDisplayHotdog->AddComponent<dae::TextureComponent>();
		toLivesDisplayHotdog->GetTransform().SetLocalPosition(10, 250, 0);
		toLivesDisplayHotdog->AddComponent<dae::TextComponent>()->SetFont(font);
		toLivesDisplayHotdog->AddComponent<dae::LivesObserverComponent>();

		// Score Display Hotdog
		auto toScoreDisplayHotdog = std::make_unique<dae::GameObject>("Background");
		toScoreDisplayHotdog->AddComponent<dae::TextureComponent>();
		toScoreDisplayHotdog->GetTransform().SetLocalPosition(10, 275, 0);
		toScoreDisplayHotdog->AddComponent<dae::TextComponent>()->SetFont(font);
		toScoreDisplayHotdog->AddComponent<dae::ScoreObserverComponent>();

		// Observers
		// Observe Chef
		goc->AddComponent<dae::LivesComponent>();
		goc->AddComponent<dae::ScoreComponent>();
		goc->GetComponent<dae::LivesComponent>()->AddObserver(toLivesDisplayChef->GetComponent<dae::LivesObserverComponent>());
		goc->GetComponent<dae::ScoreComponent>()->AddObserver(toScoreDisplayChef->GetComponent<dae::ScoreObserverComponent>());

		// Observe Hotdog
		gob->AddComponent<dae::LivesComponent>();
		gob->AddComponent<dae::ScoreComponent>();
		gob->GetComponent<dae::LivesComponent>()->AddObserver(toLivesDisplayHotdog->GetComponent<dae::LivesObserverComponent>());
		gob->GetComponent<dae::ScoreComponent>()->AddObserver(toScoreDisplayHotdog->GetComponent<dae::ScoreObserverComponent>());

		scene.Add(std::move(toLivesDisplayChef));
		scene.Add(std::move(toScoreDisplayChef));
		scene.Add(std::move(toLivesDisplayHotdog));
		scene.Add(std::move(toScoreDisplayHotdog));

		// Text
		auto toKill = std::make_unique<dae::GameObject>("Background");
		toKill->AddComponent<dae::TextureComponent>();
		toKill->GetTransform().SetLocalPosition(10, 150, 0);
		toKill->AddComponent<dae::TextComponent>()->SetFont(font);
		toKill->GetComponent<dae::TextComponent>()->SetText("Z/X: Kill (With Death sound)");
		scene.Add(std::move(toKill));

		auto toScore = std::make_unique<dae::GameObject>("Background");
		toScore->AddComponent<dae::TextureComponent>();
		toScore->GetTransform().SetLocalPosition(10, 175, 0);
		toScore->AddComponent<dae::TextComponent>()->SetFont(font);
		toScore->GetComponent<dae::TextComponent>()->SetText("C/V: Score Up");
		scene.Add(std::move(toScore));

		//{
		//	// Must Remove Commands Before Killing
		//	input.RemoveCommand("Demo", SDL_SCANCODE_Z, dae::keyState::isDown);
		//	input.RemoveCommand("Demo", SDL_SCANCODE_C, dae::keyState::isDown);
		//	input.RemoveCommand("Demo", SDL_SCANCODE_UP, dae::keyState::isHeld);
		//	input.RemoveCommand("Demo", SDL_SCANCODE_DOWN, dae::keyState::isHeld);
		//	input.RemoveCommand("Demo", SDL_SCANCODE_LEFT, dae::keyState::isHeld);
		//	input.RemoveCommand("Demo", SDL_SCANCODE_RIGHT, dae::keyState::isHeld);
		//	// Try to remove a non existing command
		//	input.RemoveCommand("Demo", SDL_SCANCODE_Q, dae::keyState::isUp);
		//	// Mark For Deletion
		//	goc->Kill();
		//}

		scene.Add(std::move(goc));
		scene.Add(std::move(gob));

		// Register objects to platform
		staticObj->GetComponent<dae::PlatformComponent>()->RegisterObjects("Demo");
		scene.Add(std::move(staticObj));
		platformObj->GetComponent<dae::PlatformComponent>()->RegisterObjects("Demo");
		scene.Add(std::move(platformObj));
	}*/

	// Level1
	{
		// Create the scene
		auto& scene = sceneManager.CreateScene("Level1");
		scene.GetSceneName();
		// Load the level
		dae::LevelLoader::GetInstance().LoadLevel("Level1.json", "Level1");
		dae::LevelLoader::GetInstance().LoadLevel("Level1.json", "Versus");
		dae::LevelLoader::GetInstance().LoadLevel("Level1.json", "Multiplayer");
		//dae::LevelLoader::GetInstance().LoadLevel("Level2.json", "Level2");
		//dae::LevelLoader::GetInstance().LoadLevel("Level3.json", "Level3");
		//dae::LevelLoader::GetInstance().LoadLevel("Level2.json", "Multiplayer");
		//dae::LevelLoader::GetInstance().LoadLevel("Level2.json", "Multiplayer");
	}

	input.AddGlobalCommand(SDL_SCANCODE_F1, dae::keyState::isDown, std::make_unique<dae::SceneNextCommand>());
	input.AddGlobalCommand(SDL_SCANCODE_F2, dae::keyState::isDown, std::make_unique<dae::MultiplayerCommand>());
	input.AddGlobalCommand(SDL_SCANCODE_F3, dae::keyState::isDown, std::make_unique<dae::VersusCommand>());
	input.AddGlobalCommand(SDL_SCANCODE_M, dae::keyState::isDown, std::make_unique<dae::ToggleSoundCommand>());

	sceneManager.SetActiveScene("Menu");
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	dae::LevelLoader::GetInstance().Init(dae::ResourceManager::GetInstance().GetDataPath());
	engine.Run(load);
	return 0;
}