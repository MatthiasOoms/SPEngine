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

void load()
{
#if _DEBUG
	dae::SoundServiceLocator::RegisterSoundSystem(
		std::make_unique<dae::LoggingSoundSystem>(std::make_unique<dae::SDLSoundSystem>())
	);
#else
	dae::SoundServiceLocator::RegisterSoundSystem(std::make_unique<dae::SDLSoundSystem>());
#endif

	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	auto& soundSystem = dae::SoundServiceLocator::GetSoundSystem();
	auto& resourceManager = dae::ResourceManager::GetInstance();
	auto& input = dae::InputManager::GetInstance();

	// Load and Play Sound
	soundSystem.Load("../Data/Death.mp3");
	soundSystem.Play(0, 100);

	// Controllers
	input.AddControllersMax();

	// Background
	auto go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("background.tga"));
	scene.Add(std::move(go));

	// Logo
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("logo.tga"));
	go->GetTransform().SetWorldPosition(216, 180, 0);
	scene.Add(std::move(go));

	// Text
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>();
	go->AddComponent<dae::TextComponent>()->SetFont(font);
	go->GetComponent<dae::TextComponent>()->SetText("Programming 4 Assignment");
	go->GetTransform().SetWorldPosition(80, 20, 0);
	scene.Add(std::move(go));

	// FPS
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>();
	go->AddComponent<dae::TextComponent>()->SetFont(font);
	go->AddComponent<dae::FPSComponent>();
	scene.Add(std::move(go));

	// Pivot point
	/*go = std::make_unique<dae::GameObject>();
	go->GetTransform().SetWorldPosition(310, 300, 0);
	scene.Add(std::move(go));*/

	// Chef
	auto goc = std::make_unique<dae::GameObject>();
	goc->AddComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("BurgerTimeChef.png"));
	goc->GetTransform().SetLocalPosition(50, 0, 0);
	//goc->AddComponent<dae::RotationComponent>();

	// Bean
	auto gob = std::make_unique<dae::GameObject>();
	//gob->SetParent(goc.get(), false);
	gob->AddComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("BurgerTimeBean.png"));
	gob->GetTransform().SetLocalPosition(20, 0, 0);
	//gob->AddComponent<dae::RotationComponent>();
	//gob->GetComponent<dae::RotationComponent>()->SetRotationSpeed(360.f);



	// Input
	// Controller
	// Move
	input.AddCommand(static_cast<int>(dae::Controller::ControllerIdx::Second), dae::Controller::ControllerButton::DPadRight, dae::keyState::isHeld, std::make_unique<dae::MoveCommand>(gob.get(), glm::vec3{1, 0, 0}, 200.f));
	input.AddCommand(static_cast<int>(dae::Controller::ControllerIdx::Second), dae::Controller::ControllerButton::DPadLeft, dae::keyState::isHeld, std::make_unique<dae::MoveCommand>(gob.get(), glm::vec3{-1, 0, 0}, 200.f));
	input.AddCommand(static_cast<int>(dae::Controller::ControllerIdx::Second), dae::Controller::ControllerButton::DPadUp, dae::keyState::isHeld,	  std::make_unique<dae::MoveCommand>(gob.get(), glm::vec3{0, -1, 0}, 200.f));
	input.AddCommand(static_cast<int>(dae::Controller::ControllerIdx::Second), dae::Controller::ControllerButton::DPadDown, dae::keyState::isHeld,  std::make_unique<dae::MoveCommand>(gob.get(), glm::vec3{0, 1, 0}, 200.f));
	// Move
	input.AddCommand(static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadRight, dae::keyState::isHeld, std::make_unique<dae::MoveCommand>(goc.get(), glm::vec3{1, 0, 0}, 400.f));
	input.AddCommand(static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadLeft, dae::keyState::isHeld, std::make_unique<dae::MoveCommand>(goc.get(), glm::vec3{-1, 0, 0}, 400.f));
	input.AddCommand(static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadUp, dae::keyState::isHeld,	  std::make_unique<dae::MoveCommand>(goc.get(), glm::vec3{0, -1, 0}, 400.f));
	input.AddCommand(static_cast<int>(dae::Controller::ControllerIdx::First), dae::Controller::ControllerButton::DPadDown, dae::keyState::isHeld,  std::make_unique<dae::MoveCommand>(goc.get(), glm::vec3{0, 1, 0}, 400.f));


	// Keyboard
	// Move
	input.AddCommand(SDL_SCANCODE_W, dae::keyState::isHeld, std::make_unique<dae::MoveCommand>(gob.get(), glm::vec3{ 0, -1, 0 }, 200.f));
	input.AddCommand(SDL_SCANCODE_A, dae::keyState::isHeld, std::make_unique<dae::MoveCommand>(gob.get(), glm::vec3{ -1, 0, 0 }, 200.f));
	input.AddCommand(SDL_SCANCODE_S, dae::keyState::isHeld, std::make_unique<dae::MoveCommand>(gob.get(), glm::vec3{ 0, 1, 0 }, 200.f));
	input.AddCommand(SDL_SCANCODE_D, dae::keyState::isHeld, std::make_unique<dae::MoveCommand>(gob.get(), glm::vec3{ 1, 0, 0 }, 200.f));
	// Move
	input.AddCommand(SDL_SCANCODE_UP, dae::keyState::isHeld, std::make_unique<dae::MoveCommand>(goc.get(), glm::vec3{ 0, -1, 0 }, 400.f));
	input.AddCommand(SDL_SCANCODE_LEFT, dae::keyState::isHeld, std::make_unique<dae::MoveCommand>(goc.get(), glm::vec3{ -1, 0, 0 }, 400.f));
	input.AddCommand(SDL_SCANCODE_DOWN, dae::keyState::isHeld, std::make_unique<dae::MoveCommand>(goc.get(), glm::vec3{ 0, 1, 0 }, 400.f));
	input.AddCommand(SDL_SCANCODE_RIGHT, dae::keyState::isHeld, std::make_unique<dae::MoveCommand>(goc.get(), glm::vec3{ 1, 0, 0 }, 400.f));

	// Print Controls
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>();
	go->AddComponent<dae::TextComponent>()->SetFont(font);
	go->GetComponent<dae::TextComponent>()->SetText("WASD or DPad to control the Bean (Second controller)");
	go->GetTransform().SetWorldPosition(10, 75, 0);
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>();
	go->AddComponent<dae::TextComponent>()->SetFont(font);
	go->GetComponent<dae::TextComponent>()->SetText("Arrows or DPad to control the Chef (First controller)");
	go->GetTransform().SetWorldPosition(10, 100, 0);
	scene.Add(std::move(go));

	// Kill
	input.AddCommand(SDL_SCANCODE_Z, dae::keyState::isDown, std::make_unique<dae::KillCommand>(goc.get()));
	input.AddCommand(SDL_SCANCODE_X, dae::keyState::isDown, std::make_unique<dae::KillCommand>(gob.get()));
	// Score
	input.AddCommand(SDL_SCANCODE_C, dae::keyState::isDown, std::make_unique<dae::ScoreSmallCommand>(goc.get()));
	input.AddCommand(SDL_SCANCODE_V, dae::keyState::isDown, std::make_unique<dae::ScoreSmallCommand>(gob.get()));

	// Lives Display Pengo
	auto toLivesDisplayChef = std::make_unique<dae::GameObject>();
	toLivesDisplayChef->AddComponent<dae::TextureComponent>();
	toLivesDisplayChef->GetTransform().SetLocalPosition(10, 200, 0);
	toLivesDisplayChef->AddComponent<dae::TextComponent>()->SetFont(font);
	toLivesDisplayChef->AddComponent<dae::LivesObserverComponent>();

	// Score Display Pengo
	auto toScoreDisplayChef = std::make_unique<dae::GameObject>();
	toScoreDisplayChef->AddComponent<dae::TextureComponent>();
	toScoreDisplayChef->GetTransform().SetLocalPosition(10, 225, 0);
	toScoreDisplayChef->AddComponent<dae::TextComponent>()->SetFont(font);
	toScoreDisplayChef->AddComponent<dae::ScoreObserverComponent>();

	// Lives Display SnoBee
	auto toLivesDisplayBean = std::make_unique<dae::GameObject>();
	toLivesDisplayBean->AddComponent<dae::TextureComponent>();
	toLivesDisplayBean->GetTransform().SetLocalPosition(10, 250, 0);
	toLivesDisplayBean->AddComponent<dae::TextComponent>()->SetFont(font);
	toLivesDisplayBean->AddComponent<dae::LivesObserverComponent>();

	// Score Display SnoBee
	auto toScoreDisplayBean = std::make_unique<dae::GameObject>();
	toScoreDisplayBean->AddComponent<dae::TextureComponent>();
	toScoreDisplayBean->GetTransform().SetLocalPosition(10, 275, 0);
	toScoreDisplayBean->AddComponent<dae::TextComponent>()->SetFont(font);
	toScoreDisplayBean->AddComponent<dae::ScoreObserverComponent>();

	// Observers
	// Observe Pengo
	goc->AddComponent<dae::LivesComponent>();
	goc->AddComponent<dae::ScoreComponent>();
	goc->GetComponent<dae::LivesComponent>()->AddObserver(toLivesDisplayChef->GetComponent<dae::LivesObserverComponent>());
	goc->GetComponent<dae::ScoreComponent>()->AddObserver(toScoreDisplayChef->GetComponent<dae::ScoreObserverComponent>());
	//goc->GetComponent<dae::ScoreComponent>()->AddObserver(oAchievementHandler->GetComponent<dae::AchievementsObserverComponent>());
	// Observe SnoBee
	gob->AddComponent<dae::LivesComponent>();
	gob->AddComponent<dae::ScoreComponent>();
	gob->GetComponent<dae::LivesComponent>()->AddObserver(toLivesDisplayBean->GetComponent<dae::LivesObserverComponent>());
	gob->GetComponent<dae::ScoreComponent>()->AddObserver(toScoreDisplayBean->GetComponent<dae::ScoreObserverComponent>());
	//gob->GetComponent<dae::ScoreComponent>()->AddObserver(oAchievementHandler->GetComponent<dae::AchievementsObserverComponent>());

	scene.Add(std::move(toLivesDisplayChef));
	scene.Add(std::move(toScoreDisplayChef));
	scene.Add(std::move(toLivesDisplayBean));
	scene.Add(std::move(toScoreDisplayBean));

	// Events
	// Death
	// Separate getting the component and lowering the lives to prevent calling on nullptr
	auto livesComp = goc->GetComponent<dae::LivesComponent>();
	if (livesComp)
	{
		livesComp->LowerLives(2);
	}

	livesComp = gob->GetComponent<dae::LivesComponent>();
	if (livesComp)
	{
		livesComp->LowerLives();
	}

	// Score
	// Separate getting the component and lowering the lives to prevent calling on nullptr
	auto scoreComp = goc->GetComponent<dae::ScoreComponent>();
	if (scoreComp)
	{
		scoreComp->IncreaseScore(100);
	}
	scoreComp = gob->GetComponent<dae::ScoreComponent>();
	if (scoreComp)
	{
		scoreComp->SetScore(50);
	}

	// Text
	auto toKill = std::make_unique<dae::GameObject>();
	toKill->AddComponent<dae::TextureComponent>();
	toKill->GetTransform().SetLocalPosition(10, 150, 0);
	toKill->AddComponent<dae::TextComponent>()->SetFont(font);
	toKill->GetComponent<dae::TextComponent>()->SetText("Z/X: Kill");
	scene.Add(std::move(toKill));

	auto toScore = std::make_unique<dae::GameObject>();
	toScore->AddComponent<dae::TextureComponent>();
	toScore->GetTransform().SetLocalPosition(10, 175, 0);
	toScore->AddComponent<dae::TextComponent>()->SetFont(font);
	toScore->GetComponent<dae::TextComponent>()->SetText("C/V: Score Up");
	scene.Add(std::move(toScore));

	/*{
		// Must Remove Commands Before Killing
		input.RemoveCommand(SDL_SCANCODE_Z, dae::keyState::isDown);
		input.RemoveCommand(SDL_SCANCODE_C, dae::keyState::isDown);
		input.RemoveCommand(SDL_SCANCODE_UP, dae::keyState::isHeld);
		input.RemoveCommand(SDL_SCANCODE_DOWN, dae::keyState::isHeld);
		input.RemoveCommand(SDL_SCANCODE_LEFT, dae::keyState::isHeld);
		input.RemoveCommand(SDL_SCANCODE_RIGHT, dae::keyState::isHeld);
		// Try to remove a non existing command
		input.RemoveCommand(SDL_SCANCODE_Q, dae::keyState::isUp);
		// Mark For Deletion
		goc->Kill();
	}*/

	scene.Add(std::move(goc));
	scene.Add(std::move(gob));
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}