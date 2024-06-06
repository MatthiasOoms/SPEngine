#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include "Singleton.h"
#include <vector>
#include <string>
#include <memory>

namespace dae
{
	class Scene;

	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		void SetActiveScene(std::string name);
		dae::Scene& GetActiveScene() const { return *m_ActiveScene; }
		dae::Scene& GetNextScene(std::string scene) const;
		dae::Scene& GetScene(std::string scene) const;
		bool HasScene(std::string scene) const;

		void Update(const float deltaTime);
		void Render(const float deltaTime) const;
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::shared_ptr<Scene> m_ActiveScene;
	};
}

#endif // ! SCENEMANAGER_H
