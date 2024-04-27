#pragma once
#include <string>

namespace dae
{
	using sound_name = std::string;

	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void Play(const sound_name id, const float volume) = 0;
		virtual void Pause() = 0;
		virtual void Resume() = 0;
		virtual void Stop() = 0;
		virtual bool Load(const std::string& filePath) = 0;
	};
}