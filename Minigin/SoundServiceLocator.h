#ifndef SOUND_SERVICE_LOCATOR_H
#define SOUND_SERVICE_LOCATOR_H
#include <memory>

namespace dae
{
	class SoundSystem;

	class SoundServiceLocator final
	{
	private:
		static std::unique_ptr<dae::SoundSystem> m_pInstance;

	public:
		static SoundSystem& GetSoundSystem();
		static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& ss);
	};
}

#endif // !SOUND_SERVICE_LOCATOR_H