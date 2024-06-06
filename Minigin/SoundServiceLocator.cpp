#include "SoundServiceLocator.h"
#include "NullSoundSystem.h"

std::unique_ptr<dae::SoundSystem> dae::SoundServiceLocator::m_pInstance = std::make_unique<dae::NullSoundSystem>();

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