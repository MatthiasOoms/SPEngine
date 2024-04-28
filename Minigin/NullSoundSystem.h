#pragma once
#include "SoundSystem.h"
#include <string>

namespace dae
{
	class NullSoundSystem final : public SoundSystem
	{
	private:
		void InternalPlay(Sound) override {};

	public:
		void Play(Sound) override {};
		void PlayMusic(Sound music) {};
		void PauseSoundEffects() override {};
		void PauseMusic() {};
		void ResumeSoundEffects() override {};
		void ResumeMusic() override {};
		void CheckQueue() override {};
		void PushOnQueue(Sound) override {};
		void Stop() override {};
		bool Load(Sound) override { return true; };
	};
}