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
		void Pause() override;
		void Resume() override;
		void CheckQueue() override;
		void PushOnQueue(Sound audio) override;
		void Stop() override;
		bool Load(Sound audio) override;
		~SDLSoundSystem() override;
	};
}