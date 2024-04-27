#pragma once
#include "SoundSystem.h"
#include <string>

namespace dae
{
	class NullSoundSystem final : public SoundSystem
	{
		void Play(const sound_id, const float) override {}
		void Pause() override {};
		void Resume() override {};
		void Stop() override {};
		void Load(const std::string&) override {};
	};
}