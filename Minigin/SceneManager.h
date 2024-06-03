#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;

	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		void SetActiveScene(std::string name);
		std::shared_ptr<Scene> GetActiveScene() const { return m_ActiveScene; }
		std::shared_ptr<Scene> GetNextScene(std::string scene) const;
		std::shared_ptr<Scene> GetScene(std::string scene) const;

		void Update(const float deltaTime);
		void Render(const float deltaTime) const;
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::shared_ptr<Scene> m_ActiveScene;
	};
}
