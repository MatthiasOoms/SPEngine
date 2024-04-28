#pragma once
#include "SoundSystem.h"
#include <string>

namespace dae
{
	class SDLSoundSystem final : public SoundSystem
	{
		class SDLSoundSystemImpl;
		SDLSoundSystemImpl* pImpl;

		void InternalPlay(Sound audio) override;
	public:
		SDLSoundSystem();
		void Play(Sound audio) override;
		void PlayMusic(Sound music) override;
		void PauseSoundEffects() override;
		void PauseMusic() override;
		void ResumeSoundEffects() override;
		void ResumeMusic() override;
		void CheckQueue() override;
		void PushOnQueue(Sound audio) override;
		void Stop() override;
		bool Load(Sound audio) override;
		~SDLSoundSystem() override;
	};
}