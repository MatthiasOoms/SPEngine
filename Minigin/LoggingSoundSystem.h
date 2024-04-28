#pragma once
#include <memory>
#include "SoundSystem.h"
#include <iostream>

namespace dae
{
	class LoggingSoundSystem final : public SoundSystem
	{
		std::unique_ptr<SoundSystem> _real_ss;
		void InternalPlay(Sound audio) override;
	public:
		LoggingSoundSystem(std::unique_ptr<SoundSystem>&& ss);
		virtual ~LoggingSoundSystem() = default;
		void Play(Sound audio) override;
		void PlayMusic(Sound music) override;
		void PauseSoundEffects() override;
		void PauseMusic() override;
		void ResumeSoundEffects() override;
		void ResumeMusic() override;
		void CheckQueue() override;
		void PushOnQueue(Sound audio) override;
		void Stop() override;
		void Load(Sound audio) override;
	};
}