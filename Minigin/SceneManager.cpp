#include <stdexcept>
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
	if (name == "Multiplayer")
	{
		const auto& scene = std::shared_ptr<Scene>(new Scene(name));
		m_MultiplayerScene = scene;
		return *scene;
	}
	else if (name == "Versus")
	{
		const auto& scene = std::shared_ptr<Scene>(new Scene(name));
		m_VersusScene = scene;
		return *scene;
	}
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	if (m_Scenes.empty())
	{
		m_ActiveScene = scene;
	}
	m_Scenes.push_back(scene);
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

void dae::SceneManager::SetActiveMultiplayerScene()
{
	if (m_MultiplayerScene.get())
	{
		m_ActiveScene = m_MultiplayerScene;
	}
	else
	{
		throw std::exception("Multiplayer scene not found");
	}
}

void dae::SceneManager::SetActiveVersusScene()
{
	if (m_VersusScene.get())
	{
		m_ActiveScene = m_VersusScene;
	}
	else
	{
		throw std::exception("Versus scene not found");
	}
}

dae::Scene& dae::SceneManager::GetNextScene(std::string scene) const
{
	auto& sceneName = m_ActiveScene->GetSceneName();
	bool returnNext = false;
	// Loop through all scenes
	for (const auto& s : m_Scenes)
	{
		// If we are the scene to be returned
		if (returnNext)
		{
			return *s;
		}
		// If the current scene is the active scene
		if (s->GetSceneName() == sceneName)
		{
			// Then we must return the next scene
			returnNext = true;
		}
	}
	return *m_Scenes.front();
}

dae::Scene& dae::SceneManager::GetScene(std::string scene) const
{
	for (const auto& s : m_Scenes)
	{
		if (s->GetSceneName() == scene)
		{
			return *s;
		}
	}

	if (scene == "Multiplayer" && m_MultiplayerScene.get())
	{
		return *m_MultiplayerScene;
	}
	else if (scene == "Versus" && m_VersusScene.get())
	{
		return *m_VersusScene;
	}

	throw std::runtime_error("Scene not found: " + scene);
}

bool dae::SceneManager::HasScene(std::string scene) const
{
	for (const auto& s : m_Scenes)
	{
		if (s->GetSceneName() == scene)
		{
			return true;
		}
	}
	
	if (scene == "Multiplayer" && m_MultiplayerScene.get())
	{
		return true;
	}
	else if (scene == "Versus" && m_VersusScene.get())
	{
		return true;
	}

	return false;
}
