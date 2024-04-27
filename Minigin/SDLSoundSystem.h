#pragma once
#include "SoundSystem.h"
#include <string>

namespace dae
{
	class SDLSoundSystem final : public SoundSystem
	{
		class SDLSoundSystemImpl;
		SDLSoundSystemImpl* pImpl;
	public:
		SDLSoundSystem();
		void Play(const sound_id id, const float volume) override;
		void Pause() override;
		void Resume() override;
		void Stop() override;
		void Load(const std::string& filePath) override;
		~SDLSoundSystem() override;
	};
}