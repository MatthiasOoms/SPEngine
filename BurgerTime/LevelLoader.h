#include <Scene.h>
#ifndef LEVELLOADER_H
#define LEVELLOADER_H
#include "Singleton.h"
#include <string>

namespace dae
{
	class GameObject;

	class LevelLoader : public Singleton<LevelLoader>
	{
	public:
		void Init(const std::string& data);
		void LoadLevel(const std::string& fileName, const std::string& sceneName);

		// A templated function for calling RegisterObject on all the objects in the level
		template <typename T>
		void RegisterObjects(const std::string& objectTag, const std::string& sceneName)
		{
			// Add the GameObjects to the scene
			auto& sceneManager = SceneManager::GetInstance();
			auto& scene = sceneManager.GetScene(sceneName);

			// Get all Plate Objects
			auto objects = scene.GetObjectsByTag(objectTag);
			// Register all objects to PlateComponent
			for (auto& obj : objects)
			{
				if (obj->HasComponent<T>())
				{
					obj->GetComponent<T>()->RegisterObjects(sceneName);
				}
			}
		}

	private:
		std::vector<std::unique_ptr<dae::GameObject>> CreateIngredient(std::string type, float x, float y, int id);
		friend class Singleton<LevelLoader>;
		LevelLoader() = default;
		std::string m_dataPath;
	};
}

#endif // ! LEVELLOADER_H
