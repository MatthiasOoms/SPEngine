#pragma once
#include "SoundSystem.h"
#include <string>
#include "SoundServiceLocator.h"
#include <queue>

namespace dae
{
	class NullSoundSystem final : public SoundSystem
	{
	private:
		void InternalPlay(Sound) override {};

	public:
		void PlaySoundEffect(Sound) override {};
		void PlayMusic(Sound music) {};
		void PauseSoundEffects() override {};
		void PauseMusic() {};
		void ResumeSoundEffects() override {};
		void ResumeMusic() override {};
		void PushOnQueue(Sound audio) override {};
		void StopSoundEffects() override {};
		void StopMusic() override {};
		void Load(Sound) override {};
	};
}