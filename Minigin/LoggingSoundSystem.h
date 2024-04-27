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
		void Pause() override;
		void Resume() override;
		void CheckQueue() override;
		void PushOnQueue(Sound audio) override;
		void Stop() override;
		bool Load(Sound audio) override;
	};
}