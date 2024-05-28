#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(const float deltaTime)
{
	if (m_ActiveScene.get())
	{
		m_ActiveScene->Update(deltaTime);
	}
}

void dae::SceneManager::Render(const float deltaTime) const
{
	if (m_ActiveScene.get())
	{
		m_ActiveScene->Render(deltaTime);
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	m_ActiveScene = scene;
	return *scene;
}

void dae::SceneManager::SetActiveScene(std::string name)
{
	for (const auto& scene : m_Scenes)
	{
		if (scene->GetSceneName() == name)
		{
			m_ActiveScene = scene;
			return;
		}
	}

	throw std::exception("Scene not found");
}
