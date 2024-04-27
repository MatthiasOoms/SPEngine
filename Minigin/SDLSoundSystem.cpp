#include "SDLSoundSystem.h"
#include <iostream>
#include <thread>
#include <string>
#include <queue>
#include <mutex>
#include <map>

#include <SDL.h>
#include <SDL_mixer.h> 
#include "SoundServiceLocator.h"

class dae::SDLSoundSystem::SDLSoundSystemImpl
{
private:
	std::map<const sound_name, Mix_Chunk*> m_pSoundEffects;
	std::mutex m_SoundEffectsMutex{};
	std::queue<Sound> m_Queue;
	// std::jthread m_Thread{};

	void InternalPlay(Sound audio)
	{
		if (m_pSoundEffects.count(audio.name) <= 0)
		{
			std::cerr << "Sound name not found: " << audio.name << std::endl;
			return;
		}

		Mix_Chunk* soundEffect{ m_pSoundEffects[audio.name] }; // Put current sound in there

		if (soundEffect == nullptr)
		{
			std::cerr << "Invalid sound for name: " << audio.name << std::endl;
			return;
		}

		int channel = Mix_PlayChannel(-1, soundEffect, audio.loops);
		if (channel == -1)
		{
			std::cerr << "Failed to play sound: " << Mix_GetError() << std::endl;
			return;
		}

		Mix_Volume(channel, static_cast<int>(audio.volume * MIX_MAX_VOLUME));
	}

public:
	void Play(Sound audio)
	{
		InternalPlay(audio);
	}

	void Pause()
	{
		Mix_Pause(-1);
	}

	void Resume()
	{
		Mix_Resume(-1);
	}

	void Stop()
	{
		Mix_HaltChannel(-1);
	}

	bool Load(Sound audio)
	{
		bool loaded = false;
		std::jthread soundLoaderThread([this, audio, &loaded]()
			{
				// Check if the sound is already loaded
				if (m_pSoundEffects.count(audio.name) <= 0)
				{
					// If not, load the sound
					Mix_Chunk* soundEffect = Mix_LoadWAV(audio.filePath.c_str());

					// Check if the sound is loaded
					if (soundEffect == nullptr)
					{
						std::cout << "Failed to load sound effect: " << Mix_GetError() << std::endl;
						return;
					}
					// If success, add it to the map
					std::lock_guard<std::mutex> lock(m_SoundEffectsMutex);
					m_pSoundEffects.emplace(std::make_pair(audio.name, soundEffect));
				}
				loaded = true;
			}
		);

		soundLoaderThread.join();
		return loaded;
	}

	void CheckQueue()
	{
		// Check if the queue is empty
		while (m_Queue.size() > 0)
		{
			// Get the sound system (SDL or Logging)
			auto& soundSystem = dae::SoundServiceLocator::GetSoundSystem();

			// Load the oldest object in the Queue
			soundSystem.Load(m_Queue.front());

			// If the sound is loaded, play it
			if (m_pSoundEffects.count(m_Queue.front().name))
			{
				// Play the sound
				soundSystem.Play(m_Queue.front());
			}

			// Remove the sound from the queue
			m_Queue.pop();
		}
	}

	void PushOnQueue(Sound audio)
	{
		m_Queue.push(audio);
	}

	void Cleanup()
	{
		for (auto sound : m_pSoundEffects)
		{
			Mix_FreeChunk(sound.second);
		}

		Mix_CloseAudio();
		Mix_Quit();
		SDL_Quit();
	}
};

void dae::SDLSoundSystem::InternalPlay(Sound audio)
{
	pImpl->Play(audio);
}

dae::SDLSoundSystem::SDLSoundSystem()
{
	if (Mix_Init(SDL_INIT_AUDIO) < 0)
	{
		std::cout << "SDL_mixer initialization failed: " << SDL_GetError() << std::endl;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL_mixer OpenAudio failed: " << Mix_GetError() << std::endl;
	}

	pImpl = new SDLSoundSystemImpl{};
}

void dae::SDLSoundSystem::Play(Sound audio)
{
	pImpl->Play(audio);
}

void dae::SDLSoundSystem::Pause()
{
	pImpl->Pause();
}

void dae::SDLSoundSystem::Resume()
{
	pImpl->Resume();
}

void dae::SDLSoundSystem::CheckQueue()
{
	pImpl->CheckQueue();
}

void dae::SDLSoundSystem::PushOnQueue(Sound audio)
{
	pImpl->PushOnQueue(audio);
}

void dae::SDLSoundSystem::Stop()
{
	pImpl->Stop();
}

bool dae::SDLSoundSystem::Load(Sound audio)
{
	return pImpl->Load(audio);
}

dae::SDLSoundSystem::~SDLSoundSystem()
{
	pImpl->Cleanup();

	delete pImpl;
	pImpl = nullptr;
}