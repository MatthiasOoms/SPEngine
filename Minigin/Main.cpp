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
	scene.Add(goc);

	// Bean
	auto gob = std::make_shared<dae::GameObject>();
	//gob->SetParent(goc.get(), false);
	gob->AddComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("BurgerTimeBean.png"));
	gob->GetTransform().SetLocalPosition(20, 0, 0);
	//gob->AddComponent<dae::RotationComponent>();
	//gob->GetComponent<dae::RotationComponent>()->SetRotationSpeed(360.f);
	scene.Add(gob);

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
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}