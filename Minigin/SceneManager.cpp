#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(const float deltaTime)
{
	for(auto& scene : m_scenes)
	{
		scene->Update(deltaTime);
	}
}

void dae::SceneManager::Render(const float deltaTime) const
{
	for (const auto& scene : m_scenes)
	{
		scene->Render(deltaTime);
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}
