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

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	auto& resourceManager = dae::ResourceManager::GetInstance();

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
	go = std::make_shared<dae::GameObject>();
	go->GetTransform().SetWorldPosition(310, 300, 0);
	scene.Add(go);

	// Chef
	go = std::make_shared<dae::GameObject>(go.get());
	go->AddComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("BurgerTimeChef.png"));
	go->GetTransform().SetLocalPosition(50, 0, 0);
	go->AddComponent<dae::RotationComponent>();
	scene.Add(go);

	// Bean
	go = std::make_shared<dae::GameObject>(go.get());
	go->AddComponent<dae::TextureComponent>()->SetTexture(resourceManager.LoadTexture("BurgerTimeBean.png"));
	go->GetTransform().SetLocalPosition(20, 0, 0);
	go->AddComponent<dae::RotationComponent>();
	go->GetComponent<dae::RotationComponent>()->SetRotationSpeed(360.f);
	scene.Add(go);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}