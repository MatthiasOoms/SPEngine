#include "SDLSoundSystem.h"
#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <mutex>
#include <map>

#include <SDL.h>
#include <SDL_mixer.h> 

class dae::SDLSoundSystem::SDLSoundSystemImpl
{
	std::map<const sound_name, Mix_Chunk*> m_pSoundEffects;
	std::mutex m_SoundEffectsMutex{};

public:
	void Play(const sound_name name, const float volume)
	{
		if (m_pSoundEffects.count(name) <= 0)
		{
			std::cerr << "Sound name not found: " << name << std::endl;
			return;
		}

		Mix_Chunk* soundEffect{ m_pSoundEffects[name] }; // Put current sound in there

		if (soundEffect == nullptr)
		{
			std::cerr << "Invalid sound for name: " << name << std::endl;
			return;
		}

		int channel = Mix_PlayChannel(-1, soundEffect, 0);
		if (channel == -1)
		{
			std::cerr << "Failed to play sound: " << Mix_GetError() << std::endl;
			return;
		}

		Mix_Volume(channel, static_cast<int>(volume * MIX_MAX_VOLUME));
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

	bool Load(const std::string& filePath)
	{
		bool loaded = false;
		std::jthread soundLoaderThread([this, filePath, &loaded]()
			{
				Mix_Chunk* soundEffect = Mix_LoadWAV(filePath.c_str());
				if (soundEffect == nullptr)
				{
					std::cerr << "Failed to load sound effect: " << Mix_GetError() << std::endl;
					loaded = false;
					return;
				}

				loaded = true;

				// Get the start of the name
				const std::string nameStart = filePath.substr(filePath.find_last_of("/") + 1);
				const std::string fileName = nameStart.substr(0, nameStart.find_last_of("."));

				// Check if the sound is already loaded
				if (m_pSoundEffects.count(fileName) <= 0)
				{
					// If not, add it to the map
					std::lock_guard<std::mutex> lock(m_SoundEffectsMutex);
					m_pSoundEffects.emplace(std::make_pair(fileName, soundEffect));
				}

				// TODO: Implement RAII like in the 2D Texture
				// Freeing the chunk removes from memory, using deleted sound
				//Mix_FreeChunk(soundEffect);
			}
		);

		soundLoaderThread.join();
		return loaded;
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

void dae::SDLSoundSystem::Play(const sound_name id, const float volume)
{
	pImpl->Play(id, volume);
}

void dae::SDLSoundSystem::Pause()
{
	pImpl->Pause();
}

void dae::SDLSoundSystem::Resume()
{
	pImpl->Resume();
}

void dae::SDLSoundSystem::Stop()
{
	pImpl->Stop();
}

bool dae::SDLSoundSystem::Load(const std::string& filePath)
{
	return pImpl->Load(filePath);
}

dae::SDLSoundSystem::~SDLSoundSystem()
{
	pImpl->Cleanup();

	delete pImpl;
	pImpl = nullptr;
}