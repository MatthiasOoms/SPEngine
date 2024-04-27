#pragma once
#include <memory>
#include "SoundSystem.h"
#include <iostream>

namespace dae
{
	class LoggingSoundSystem final : public SoundSystem
	{
		std::unique_ptr<SoundSystem> _real_ss;
	public:
		LoggingSoundSystem(std::unique_ptr<SoundSystem>&& ss);
		virtual ~LoggingSoundSystem() = default;
		void Play(const sound_name id, const float volume) override;
		void Pause() override;
		void Resume() override;
		void Stop() override;
		bool Load(const std::string& filePath) override;
	};
}