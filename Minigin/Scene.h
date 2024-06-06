#ifndef SCENE_H
#define SCENE_H
#include <string>
#include <vector>
#include <memory>
#include "GameObject.h"
#include "SceneManager.h"

namespace dae
{
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(std::unique_ptr<GameObject> object);
		void Remove(std::unique_ptr<GameObject>& object);
		void RemoveAll();

		void Update(const float deltaTime);
		void Render(const float deltaTime) const;

		const std::string& GetSceneName() const { return m_Name; }
		std::vector<GameObject*> GetObjectsByTag(std::string tag) const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector < std::unique_ptr<GameObject>> m_Objects{};

		static unsigned int m_IdCounter;
	};
}

#endif // ! SCENE_H
