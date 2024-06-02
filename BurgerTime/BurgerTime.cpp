#pragma once
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <Minigin.h>
#include <SDL.h>

#include "Scene.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
// Components
#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "RotationComponent.h"
#include "Controller.h"
#include "Command.h"
#include "InputManager.h"
#include "LivesObserverComponent.h"
#include "LivesComponent.h"
#include "ScoreObserverComponent.h"
#include "ScoreComponent.h"

#include <SDL_mixer.h>
#include "SoundServiceLocator.h"
#include "LoggingSoundSystem.h"
#include "SDLSoundSystem.h"
#include "NullSoundSystem.h"
#include "GameCommands.h"
#include "PlayerComponent.h"
#include "CollisionComponent.h"
#include "PlatformComponent.h"

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

	// Demo scene
	{
		auto& scene = sceneManager.CreateScene("Demo");

		// Load and Play Sound
		dae::Sound temp{ "../Data/Soundtrack.mp3", "Soundtrack", 1, -1 };
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
		/*go = std::make_unique<dae::GameObject>();
		go->GetTransform().SetWorldPosition(310, 300, 0);
		scene.Add(std::move(go));*/

		// Chef
		auto goc = std::make_unique<dae::GameObject>("Player");
		goc->AddComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("BurgerTimeChef.png"));
		goc->GetTransform().SetLocalPosition(50, 0, 0);
		//goc->AddComponent<dae::RotationComponent>();

		// Bean
		auto gob = std::make_unique<dae::GameObject>("Player");
		//gob->SetParent(goc.get(), false);
		gob->AddComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("BurgerTimeBean.png"));
		gob->GetTransform().SetLocalPosition(20, 0, 0);
		//gob->AddComponent<dae::RotationComponent>();
		//gob->GetComponent<dae::RotationComponent>()->SetRotationSpeed(360.f);
		


		// Collision test obj
		auto staticObj = std::make_unique<dae::GameObject>("StaticLevel");
		staticObj->AddComponent<dae::CollisionComponent>();
		staticObj->AddComponent<dae::PlatformComponent>();
		staticObj->AddComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("platform.png"));
		staticObj->GetTransform().SetWorldPosition(0, 50, 0);
		if (staticObj->HasComponent<dae::CollisionComponent>() && staticObj->HasComponent<dae::TextureComponent>())
		{
			auto platformTexture = staticObj->GetComponent<dae::TextureComponent>();
			platformTexture->SetScale(1);
			auto platformCollision = staticObj->GetComponent<dae::CollisionComponent>();
			platformCollision->SetDimensions(platformTexture->GetDimensions());
		}

		// Player Components and Collision Components
		gob->AddComponent<dae::CollisionComponent>();
		gob->AddComponent<dae::PlayerComponent>();
		if (gob->HasComponent<dae::CollisionComponent>() && gob->HasComponent<dae::TextureComponent>())
		{
			auto gobTexture = gob->GetComponent<dae::TextureComponent>();
			gobTexture->SetScale(1);
		}
		goc->AddComponent<dae::CollisionComponent>();
		goc->AddComponent<dae::PlayerComponent>();
		if (goc->HasComponent<dae::CollisionComponent>() && goc->HasComponent<dae::TextureComponent>())
		{
			auto gocTexture = goc->GetComponent<dae::TextureComponent>();
			gocTexture->SetScale(2);
			auto gocCol = goc->GetComponent<dae::CollisionComponent>();
			gocCol->SetDimensions(gocTexture->GetDimensions());
		}



		// Input
		// Controller
		// Move
		input.AddCommand("Demo", static_cast<int>(dae::Controller::ControllerIdx::Second), dae::Controller::ControllerButton::DPadRight, dae::keyState::isHeld, std::make_unique<dae::MoveCommand>(gob.get(), glm::vec3{ 1, 0, 0 }, 200.f));
		input.AddCommand("Demo", static_cast<int>(dae::Controller::ControllerIdx::Second), dae::Controller::ControllerButton::DPadLeft, dae::keyState::isHeld, std::make_unique<dae::MoveCommand>(gob.get(), glm::vec3{ -1, 0, 0 }, 200.f));
		input.AddCommand("Demo", static_cast<int>(dae::Controller::ControllerIdx::Second), dae::Controller::ControllerButton::DPadUp, dae::keyState::isHeld, std::make_unique<dae::MoveCommand>(gob.get(), glm::vec3{ 0, -1, 0 }, 200.f));
		input.AddCommand("Demo", static_cast<int>(dae::Controller::ControllerIdx::Second), dae::Controller::ControllerButton::DPadDown, dae::keyState::isHeld, std::make_unique<dae::MoveCommand>(gob.get(), glm::vec3{ 0, 1, 0 }, 200.f));
		// Move
		input.AddCommand("Demo", static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadRight, dae::keyState::isHeld, std::make_unique<dae::MoveCommand>(goc.get(), glm::vec3{ 1, 0, 0 }, 400.f));
		input.AddCommand("Demo", static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadLeft, dae::keyState::isHeld, std::make_unique<dae::MoveCommand>(goc.get(), glm::vec3{ -1, 0, 0 }, 400.f));
		input.AddCommand("Demo", static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadUp, dae::keyState::isHeld, std::make_unique<dae::MoveCommand>(goc.get(), glm::vec3{ 0, -1, 0 }, 400.f));
		input.AddCommand("Demo", static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadDown, dae::keyState::isHeld, std::make_unique<dae::MoveCommand>(goc.get(), glm::vec3{ 0, 1, 0 }, 400.f));

		// Keyboard
		{
			// Start Move
			input.AddCommand("Demo", SDL_SCANCODE_W, dae::keyState::isDown, std::make_unique<dae::ClimbStartCommand>(gob.get()));
			input.AddCommand("Demo", SDL_SCANCODE_S, dae::keyState::isDown, std::make_unique<dae::ClimbStartCommand>(gob.get()));
			input.AddCommand("Demo", SDL_SCANCODE_A, dae::keyState::isDown, std::make_unique<dae::MoveStartCommand>(gob.get()));
			input.AddCommand("Demo", SDL_SCANCODE_D, dae::keyState::isDown, std::make_unique<dae::MoveStartCommand>(gob.get()));
			// Start Move
			input.AddCommand("Demo", SDL_SCANCODE_UP, dae::keyState::isDown, std::make_unique<dae::ClimbStartCommand>(goc.get()));
			input.AddCommand("Demo", SDL_SCANCODE_DOWN, dae::keyState::isDown, std::make_unique<dae::ClimbStartCommand>(goc.get()));
			input.AddCommand("Demo", SDL_SCANCODE_LEFT, dae::keyState::isDown, std::make_unique<dae::MoveStartCommand>(goc.get()));
			input.AddCommand("Demo", SDL_SCANCODE_RIGHT, dae::keyState::isDown, std::make_unique<dae::MoveStartCommand>(goc.get()));
		}
		{
			// Move
			input.AddCommand("Demo", SDL_SCANCODE_W, dae::keyState::isHeld, std::make_unique<dae::MoveCommand>(gob.get(), glm::vec3{ 0, -1, 0 }, 200.f));
			input.AddCommand("Demo", SDL_SCANCODE_A, dae::keyState::isHeld, std::make_unique<dae::MoveCommand>(gob.get(), glm::vec3{ -1, 0, 0 }, 200.f));
			input.AddCommand("Demo", SDL_SCANCODE_S, dae::keyState::isHeld, std::make_unique<dae::MoveCommand>(gob.get(), glm::vec3{ 0, 1, 0 }, 200.f));
			input.AddCommand("Demo", SDL_SCANCODE_D, dae::keyState::isHeld, std::make_unique<dae::MoveCommand>(gob.get(), glm::vec3{ 1, 0, 0 }, 200.f));
			// Move
			input.AddCommand("Demo", SDL_SCANCODE_UP, dae::keyState::isHeld, std::make_unique<dae::MoveCommand>(goc.get(), glm::vec3{ 0, -1, 0 }, 400.f));
			input.AddCommand("Demo", SDL_SCANCODE_LEFT, dae::keyState::isHeld, std::make_unique<dae::MoveCommand>(goc.get(), glm::vec3{ -1, 0, 0 }, 400.f));
			input.AddCommand("Demo", SDL_SCANCODE_DOWN, dae::keyState::isHeld, std::make_unique<dae::MoveCommand>(goc.get(), glm::vec3{ 0, 1, 0 }, 400.f));
			input.AddCommand("Demo", SDL_SCANCODE_RIGHT, dae::keyState::isHeld, std::make_unique<dae::MoveCommand>(goc.get(), glm::vec3{ 1, 0, 0 }, 400.f));
		}
		{
			// End Move
			input.AddCommand("Demo", SDL_SCANCODE_W, dae::keyState::isUp, std::make_unique<dae::ClimbEndCommand>(gob.get()));
			input.AddCommand("Demo", SDL_SCANCODE_S, dae::keyState::isUp, std::make_unique<dae::ClimbEndCommand>(gob.get()));
			input.AddCommand("Demo", SDL_SCANCODE_A, dae::keyState::isUp, std::make_unique<dae::MoveEndCommand>(gob.get()));
			input.AddCommand("Demo", SDL_SCANCODE_D, dae::keyState::isUp, std::make_unique<dae::MoveEndCommand>(gob.get()));
			// End Move
			input.AddCommand("Demo", SDL_SCANCODE_UP, dae::keyState::isUp, std::make_unique<dae::ClimbEndCommand>(goc.get()));
			input.AddCommand("Demo", SDL_SCANCODE_DOWN, dae::keyState::isUp, std::make_unique<dae::ClimbEndCommand>(goc.get()));
			input.AddCommand("Demo", SDL_SCANCODE_LEFT, dae::keyState::isUp, std::make_unique<dae::MoveEndCommand>(goc.get()));
			input.AddCommand("Demo", SDL_SCANCODE_RIGHT, dae::keyState::isUp, std::make_unique<dae::MoveEndCommand>(goc.get()));
		}

		// Print Controls
		font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
		go = std::make_unique<dae::GameObject>("Background");
		go->AddComponent<dae::TextureComponent>();
		go->AddComponent<dae::TextComponent>()->SetFont(font);
		go->GetComponent<dae::TextComponent>()->SetText("WASD or DPad to control the Bean (Second controller)");
		go->GetTransform().SetWorldPosition(10, 75, 0);
		scene.Add(std::move(go));

		go = std::make_unique<dae::GameObject>("Background");
		go->AddComponent<dae::TextureComponent>();
		go->AddComponent<dae::TextComponent>()->SetFont(font);
		go->GetComponent<dae::TextComponent>()->SetText("Arrows or DPad to control the Chef (First controller)");
		go->GetTransform().SetWorldPosition(10, 100, 0);
		scene.Add(std::move(go));


		// Kill
		input.AddCommand("Demo", SDL_SCANCODE_Z, dae::keyState::isDown, std::make_unique<dae::KillCommand>(goc.get()));
		input.AddCommand("Demo", SDL_SCANCODE_X, dae::keyState::isDown, std::make_unique<dae::KillCommand>(gob.get()));
		// Score
		input.AddCommand("Demo", SDL_SCANCODE_C, dae::keyState::isDown, std::make_unique<dae::ScoreSmallCommand>(goc.get()));
		input.AddCommand("Demo", SDL_SCANCODE_V, dae::keyState::isDown, std::make_unique<dae::ScoreSmallCommand>(gob.get()));

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

		// Lives Display Bean
		auto toLivesDisplayBean = std::make_unique<dae::GameObject>("Background");
		toLivesDisplayBean->AddComponent<dae::TextureComponent>();
		toLivesDisplayBean->GetTransform().SetLocalPosition(10, 250, 0);
		toLivesDisplayBean->AddComponent<dae::TextComponent>()->SetFont(font);
		toLivesDisplayBean->AddComponent<dae::LivesObserverComponent>();

		// Score Display Bean
		auto toScoreDisplayBean = std::make_unique<dae::GameObject>("Background");
		toScoreDisplayBean->AddComponent<dae::TextureComponent>();
		toScoreDisplayBean->GetTransform().SetLocalPosition(10, 275, 0);
		toScoreDisplayBean->AddComponent<dae::TextComponent>()->SetFont(font);
		toScoreDisplayBean->AddComponent<dae::ScoreObserverComponent>();

		// Observers
		// Observe Chef
		goc->AddComponent<dae::LivesComponent>();
		goc->AddComponent<dae::ScoreComponent>();
		goc->GetComponent<dae::LivesComponent>()->AddObserver(toLivesDisplayChef->GetComponent<dae::LivesObserverComponent>());
		goc->GetComponent<dae::ScoreComponent>()->AddObserver(toScoreDisplayChef->GetComponent<dae::ScoreObserverComponent>());

		// Observe Bean
		gob->AddComponent<dae::LivesComponent>();
		gob->AddComponent<dae::ScoreComponent>();
		gob->GetComponent<dae::LivesComponent>()->AddObserver(toLivesDisplayBean->GetComponent<dae::LivesObserverComponent>());
		gob->GetComponent<dae::ScoreComponent>()->AddObserver(toScoreDisplayBean->GetComponent<dae::ScoreObserverComponent>());

		scene.Add(std::move(toLivesDisplayChef));
		scene.Add(std::move(toScoreDisplayChef));
		scene.Add(std::move(toLivesDisplayBean));
		scene.Add(std::move(toScoreDisplayBean));

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

		/*{
			// Must Remove Commands Before Killing
			input.RemoveCommand("Demo", SDL_SCANCODE_Z, dae::keyState::isDown);
			input.RemoveCommand("Demo", SDL_SCANCODE_C, dae::keyState::isDown);
			input.RemoveCommand("Demo", SDL_SCANCODE_UP, dae::keyState::isHeld);
			input.RemoveCommand("Demo", SDL_SCANCODE_DOWN, dae::keyState::isHeld);
			input.RemoveCommand("Demo", SDL_SCANCODE_LEFT, dae::keyState::isHeld);
			input.RemoveCommand("Demo", SDL_SCANCODE_RIGHT, dae::keyState::isHeld);
			// Try to remove a non existing command
			input.RemoveCommand("Demo", SDL_SCANCODE_Q, dae::keyState::isUp);
			// Mark For Deletion
			goc->Kill();
		}*/

		scene.Add(std::move(goc));
		scene.Add(std::move(gob));

		input.AddCommand("Demo", SDL_SCANCODE_SPACE, dae::keyState::isDown, std::make_unique<dae::SceneSwapCommand>("Menu", "../Data/Soundtrack.mp3"));
	
		// Register objects to platform
		staticObj->GetComponent<dae::PlatformComponent>()->RegisterObjects("Demo");
		scene.Add(std::move(staticObj));
	}

	// Menu scene
	{
		// Create scene
		auto& scene = sceneManager.CreateScene("Menu");

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

		input.AddCommand("Menu", SDL_SCANCODE_SPACE, dae::keyState::isDown, std::make_unique<dae::SceneSwapCommand>("Demo", "../Data/Soundtrack.mp3"));
	}

	sceneManager.SetActiveScene("Menu");
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}