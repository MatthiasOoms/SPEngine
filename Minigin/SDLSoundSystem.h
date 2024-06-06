#ifndef SDLSOUNDSYSTEM_H
#define SDLSOUNDSYSTEM_H
#include "SoundSystem.h"
#include <thread>

namespace dae
{
	class SDLSoundSystem final : public SoundSystem
	{
		class SDLSoundSystemImpl;
		SDLSoundSystemImpl* pImpl;

		std::jthread m_Thread;

		void InternalPlay(Sound audio) override;
		void CheckQueue();
	public:
		SDLSoundSystem();
		~SDLSoundSystem() override;
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
		void PushOnQueue(Sound audio);
	};
}

#endif // ! SDLSOUNDSYSTEM_H
