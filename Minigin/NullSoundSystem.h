#pragma once
#include "SoundSystem.h"
#include <string>
#include "SoundServiceLocator.h"
#include <queue>

namespace dae
{
	class NullSoundSystem final : public SoundSystem
	{
	private:
		void InternalPlay(Sound) override {};
		std::queue<Sound> m_Queue;

	public:
		void Play(Sound) override {};
		void PlayMusic(Sound music) {};
		void PauseSoundEffects() override {};
		void PauseMusic() {};
		void ResumeSoundEffects() override {};
		void ResumeMusic() override {};
		void CheckQueue() override {
			// Check if the queue is empty
			while (m_Queue.size() > 0)
			{
				// Get the sound system (SDL or Logging)
				auto& soundSystem = dae::SoundServiceLocator::GetSoundSystem();

				// Load the oldest object in the Queue
				soundSystem.Load(m_Queue.front());

				// Play the sound
				soundSystem.Play(m_Queue.front());

				// Remove the sound from the queue
				m_Queue.pop();
			}
		};
		void PushOnQueue(Sound audio) override { m_Queue.push(audio); };
		void Stop() override {};
		void Load(Sound) override {};
	};
}