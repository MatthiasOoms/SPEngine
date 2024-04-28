#include "SoundServiceLocator.h"
#include "NullSoundSystem.h"
//#include "SDLSoundSystem.h"

std::unique_ptr<dae::SoundSystem> dae::SoundServiceLocator::m_pInstance = nullptr;

dae::SoundSystem& dae::SoundServiceLocator::GetSoundSystem()
{
	return *m_pInstance;
}

void dae::SoundServiceLocator::RegisterSoundSystem(std::unique_ptr<SoundSystem>&& ss)
{
	if (ss == nullptr)
	{
		m_pInstance = std::make_unique<NullSoundSystem>();
	}
	else
	{
		m_pInstance = std::move(ss);
	}
}