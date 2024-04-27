#pragma once
#include "SoundSystem.h"
#include <string>

namespace dae
{
	class NullSoundSystem final : public SoundSystem
	{
		void Play(const sound_name, const float) override {}
		void Pause() override {};
		void Resume() override {};
		void Stop() override {};
		bool Load(const std::string&) override { return true; };
	};
}