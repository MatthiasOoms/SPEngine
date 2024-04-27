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
		void Pause() override {};
		void Resume() override {};
		void CheckQueue() override {};
		void PushOnQueue(Sound) override {};
		void Stop() override {};
		bool Load(Sound) override { return true; };
	};
}