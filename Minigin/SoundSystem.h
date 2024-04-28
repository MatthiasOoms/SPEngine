#pragma once
#include <string>

namespace dae
{
	using sound_name = std::string;

	struct Sound
	{
		std::string filePath;
		sound_name name;
		float volume;
		int loops;
	};

	class SoundSystem
	{
	private:
		virtual void InternalPlay(Sound audio) = 0;

	public:
		virtual ~SoundSystem() = default;
		virtual void Play(Sound audio) = 0;
		virtual void PlayMusic(Sound music) = 0;
		virtual void PauseSoundEffects() = 0;
		virtual void PauseMusic() = 0;
		virtual void ResumeSoundEffects() = 0;
		virtual void ResumeMusic() = 0;
		virtual void CheckQueue() = 0;
		virtual void PushOnQueue(Sound audio) = 0;
		virtual void Stop() = 0;
		virtual bool Load(Sound audio) = 0;
	};
}