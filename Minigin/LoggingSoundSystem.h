#ifndef LOGGINGSOUNDSYSTEM_H
#define LOGGINGSOUNDSYSTEM_H
#include "SoundSystem.h"
#include <memory>

namespace dae
{
	class LoggingSoundSystem final : public SoundSystem
	{
		std::unique_ptr<SoundSystem> _real_ss;
		void InternalPlay(Sound audio) override;
	public:
		LoggingSoundSystem(std::unique_ptr<SoundSystem>&& ss);
		virtual ~LoggingSoundSystem() = default;
		void PlaySoundEffect(Sound audio) override;
		void PlayMusic(Sound music) override;
		void PauseSoundEffects() override;
		void PauseMusic() override;
		void ResumeSoundEffects() override;
		void ResumeMusic() override;
		void StopSoundEffects() override;
		void StopMusic() override;
		void Load(Sound audio) override;
		bool ToggleMute() override;
		void SetSoundEffectVolume(float volume) override;
		void SetMusicVolume(float volume) override;
		void PushOnQueue(Sound audio) override;
	};
}

#endif // ! LOGGINGSOUNDSYSTEM_H
