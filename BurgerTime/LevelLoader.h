#pragma once
#include "Singleton.h"
#include <vector>
#include <string>
#include <memory>

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
