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

	private:
		friend class Singleton<LevelLoader>;
		LevelLoader() = default;
		std::string m_dataPath;
	};
}

#endif // ! LEVELLOADER_H
