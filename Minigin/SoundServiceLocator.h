#pragma once
#include <memory>

namespace dae
{
	class SoundSystem;

	class SoundServiceLocator final
	{
	private:
		static std::unique_ptr<SoundSystem> m_pInstance;

	public:
		static SoundSystem& GetSoundSystem();
		static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& ss);
	};
}