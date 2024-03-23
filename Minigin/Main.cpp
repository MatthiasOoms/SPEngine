#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
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
#include "CounterObserverComponent.h"
#include "CounterComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	auto& resourceManager = dae::ResourceManager::GetInstance();
	auto& input = dae::InputManager::GetInstance();

	// Controllers
	input.AddControllersMax();

	// Background
	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("background.tga"));
	scene.Add(go);

	// Logo
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("logo.tga"));
	go->GetTransform().SetWorldPosition(216, 180, 0);
	scene.Add(go);

	// Text
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>();
	go->AddComponent<dae::TextComponent>()->SetFont(font);
	go->GetComponent<dae::TextComponent>()->SetText("Programming 4 Assignment");
	go->GetTransform().SetWorldPosition(80, 20, 0);
	scene.Add(go);

	// FPS
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>();
	go->AddComponent<dae::TextComponent>()->SetFont(font);
	go->AddComponent<dae::FPSComponent>();
	scene.Add(go);

	// Pivot point
	/*go = std::make_shared<dae::GameObject>();
	go->GetTransform().SetWorldPosition(310, 300, 0);
	scene.Add(go);*/

	// Chef
	auto goc = std::make_shared<dae::GameObject>();
	goc->AddComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("BurgerTimeChef.png"));
	goc->GetTransform().SetLocalPosition(50, 0, 0);
	//goc->AddComponent<dae::RotationComponent>();

	// Bean
	auto gob = std::make_shared<dae::GameObject>();
	//gob->SetParent(goc.get(), false);
	gob->AddComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("BurgerTimeBean.png"));
	gob->GetTransform().SetLocalPosition(20, 0, 0);
	//gob->AddComponent<dae::RotationComponent>();
	//gob->GetComponent<dae::RotationComponent>()->SetRotationSpeed(360.f);

	go->Kill();

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
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>();
	go->AddComponent<dae::TextComponent>()->SetFont(font);
	go->GetComponent<dae::TextComponent>()->SetText("WASD or DPad to control the Bean (Second controller)");
	go->GetTransform().SetWorldPosition(10, 75, 0);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>();
	go->AddComponent<dae::TextComponent>()->SetFont(font);
	go->GetComponent<dae::TextComponent>()->SetText("Arrows or DPad to control the Chef (First controller)");
	go->GetTransform().SetWorldPosition(10, 100, 0);
	scene.Add(go);

	// Kill
	input.AddCommand(SDL_SCANCODE_Z, dae::keyState::isDown, std::make_unique<dae::KillCommand>(goc.get()));
	input.AddCommand(SDL_SCANCODE_X, dae::keyState::isDown, std::make_unique<dae::KillCommand>(gob.get()));
	// Score
	input.AddCommand(SDL_SCANCODE_C, dae::keyState::isDown, std::make_unique<dae::ScoreSmallCommand>(goc.get()));
	input.AddCommand(SDL_SCANCODE_V, dae::keyState::isDown, std::make_unique<dae::ScoreSmallCommand>(gob.get()));

	// Lives Display Pengo
	auto livesDisplayChef = std::make_shared<dae::GameObject>();
	livesDisplayChef->AddComponent<dae::TextureComponent>();
	livesDisplayChef->GetTransform().SetLocalPosition(10, 200, 0);
	livesDisplayChef->AddComponent<dae::TextComponent>()->SetFont(font);
	auto livesObserverChef = livesDisplayChef->AddComponent<dae::CounterObserverComponent>();
	livesObserverChef->SetSuffix(" lives");
	scene.Add(livesDisplayChef);

	// Score Display Pengo
	auto scoreDisplayChef = std::make_shared<dae::GameObject>();
	scoreDisplayChef->AddComponent<dae::TextureComponent>();
	scoreDisplayChef->GetTransform().SetLocalPosition(10, 225, 0);
	scoreDisplayChef->AddComponent<dae::TextComponent>()->SetFont(font);
	auto scoreObserverChef = scoreDisplayChef->AddComponent<dae::CounterObserverComponent>();
	scoreObserverChef->SetPrefix("Score: ");
	scene.Add(scoreDisplayChef);

	// Lives Display SnoBee
	auto livesDisplayBean = std::make_shared<dae::GameObject>();
	livesDisplayBean->AddComponent<dae::TextureComponent>();
	livesDisplayBean->GetTransform().SetLocalPosition(10, 250, 0);
	livesDisplayBean->AddComponent<dae::TextComponent>()->SetFont(font);
	auto livesObserverBean = livesDisplayBean->AddComponent<dae::CounterObserverComponent>();
	livesObserverBean->SetSuffix(" lives");
	scene.Add(livesDisplayBean);

	// Score Display SnoBee
	auto scoreDisplayBean = std::make_shared<dae::GameObject>();
	scoreDisplayBean->AddComponent<dae::TextureComponent>();
	scoreDisplayBean->GetTransform().SetLocalPosition(10, 275, 0);
	scoreDisplayBean->AddComponent<dae::TextComponent>()->SetFont(font);
	auto scoreObserverBean = scoreDisplayBean->AddComponent<dae::CounterObserverComponent>();
	scoreObserverBean->SetPrefix("Score: ");
	scene.Add(scoreDisplayBean);

	// Observer
	/*auto oAchievementHandler = std::make_shared<dae::GameObject>();
	oAchievementHandler->AddComponent<dae::AchievementsObserverComponent>();
	scene.Add(oAchievementHandler);*/

	// Observers
	// Observe Chef
	auto chefLives = goc->AddComponent<dae::CounterComponent>();
	auto chefScore = goc->AddComponent<dae::CounterComponent>();
	chefLives->SetName("Lives");
	chefScore->SetName("Score");
	chefLives->SetCount(3);
	chefLives->AddObserver(livesObserverChef);
	chefScore->AddObserver(scoreObserverChef);
	//goc->GetComponent<dae::ScoreComponent>()->AddObserver(oAchievementHandler->GetComponent<dae::AchievementsObserverComponent>());
	
	// Observe Bean
	auto beanLives = gob->AddComponent<dae::CounterComponent>();
	auto beanScore = gob->AddComponent<dae::CounterComponent>();
	beanLives->SetName("Lives");
	beanScore->SetName("Score");
	beanLives->SetCount(3);
	beanLives->AddObserver(livesObserverBean);
	beanScore->AddObserver(scoreObserverBean);
	//gob->GetComponent<dae::ScoreComponent>()->AddObserver(oAchievementHandler->GetComponent<dae::AchievementsObserverComponent>());



	// Text
	auto toKill = std::make_shared<dae::GameObject>();
	toKill->AddComponent<dae::TextureComponent>();
	toKill->GetTransform().SetLocalPosition(10, 150, 0);
	toKill->AddComponent<dae::TextComponent>()->SetFont(font);
	toKill->GetComponent<dae::TextComponent>()->SetText("Z/X: Kill");
	scene.Add(toKill);

	auto toScore = std::make_shared<dae::GameObject>();
	toScore->AddComponent<dae::TextureComponent>();
	toScore->GetTransform().SetLocalPosition(10, 175, 0);
	toScore->AddComponent<dae::TextComponent>()->SetFont(font);
	toScore->GetComponent<dae::TextComponent>()->SetText("C/V: Score Up");
	scene.Add(toScore);

	scene.Add(goc);
	scene.Add(gob);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}