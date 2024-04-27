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
		void Play(const sound_name id, const float volume) override;
		void Pause() override;
		void Resume() override;
		void Stop() override;
		bool Load(const std::string& filePath) override;
		~SDLSoundSystem() override;
	};
}