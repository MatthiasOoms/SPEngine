#include "SoundServiceLocator.h"
#include "SDLSoundSystem.h"
#include <SDL_mixer.h> 
#include <iostream>
#include <thread>
#include <string>
#include <queue>
#include <SDL.h>
#include <mutex>
#include <map>

class dae::SDLSoundSystem::SDLSoundSystemImpl
{
private:
	std::map<const sound_name, Mix_Chunk*> m_pSoundEffects;
	std::mutex m_SoundEffectsMutex{};
	std::queue<Sound> m_Queue;
	bool m_IsActive{ true };
	bool m_IsMuted{ false };
	float m_VolumeMusic{ 1 };
	float m_VolumeSoundEffects{ 1 };

	void InternalPlay(Sound audio)
	{
		// If the sound is not loaded, return
		if (m_pSoundEffects.count(audio.name) <= 0)
		{
			std::cerr << "Sound name not found: " << audio.name << std::endl;
			return;
		}

		// Get the sound effect
		Mix_Chunk* soundEffect{ m_pSoundEffects[audio.name] };

		// Check if the sound effect is valid
		if (soundEffect == nullptr)
		{
			std::cerr << "Invalid sound for name: " << audio.name << std::endl;
			return;
		}

		// Play the sound effect
		int channel = Mix_PlayChannel(-1, soundEffect, audio.loops);
		if (channel == -1)
		{
			std::cerr << "Failed to play sound: " << Mix_GetError() << std::endl;
			return;
		}
	}

public:
	void PlaySoundEffect(Sound audio)
	{
		InternalPlay(audio);
	}

	void PlayMusic(Sound music)
	{
		// Load the music
		Mix_Music* pMusic = Mix_LoadMUS(music.filePath.c_str());
		if (pMusic == nullptr)
		{
			std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
			return;
		}

		// Play the music
		if (Mix_PlayMusic(pMusic, music.loops) == -1)
		{
			std::cerr << "Failed to play music: " << Mix_GetError() << std::endl;
			return;
		}
	}

	void PauseSoundEffects()
	{
		Mix_Pause(-1);
	}

	void PauseMusic()
	{
		Mix_PauseMusic();
	}

	void ResumeSoundEffects()
	{
		Mix_Resume(-1);
	}

	void ResumeMusic()
	{
		Mix_ResumeMusic();
	}

	void StopSoundEffects()
	{
		Mix_HaltChannel(-1);
	}

	void StopMusic()
	{
		Mix_HaltMusic();
	}

	void Load(Sound audio)
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
	}

	bool ToggleMute()
	{
		// Toggle the mute
		m_IsMuted = !m_IsMuted;
		if (m_IsMuted)
		{
			// Mute the sound
			Mix_Volume(-1, static_cast<int>(0 * MIX_MAX_VOLUME));
			Mix_VolumeMusic(static_cast<int>(0 * MIX_MAX_VOLUME));
		}
		else
		{
			// Unmute the sound
			Mix_Volume(-1, static_cast<int>(m_VolumeSoundEffects * MIX_MAX_VOLUME));
			Mix_VolumeMusic(static_cast<int>(m_VolumeMusic * MIX_MAX_VOLUME));
		}
		return m_IsMuted;
	}
	
	void SetSoundEffectVolume(float vol)
	{
		// Set the volume of the sound effects
		m_VolumeSoundEffects = vol;
		Mix_Volume(-1, static_cast<int>(vol * MIX_MAX_VOLUME));
	}

	void SetMusicVolume(float vol)
	{
		// Set the volume of the music
		m_VolumeMusic = vol;
		Mix_VolumeMusic(static_cast<int>(vol * MIX_MAX_VOLUME));
	}

	void CheckQueue()
	{
		while (m_IsActive)
		{
			// Check if the queue is empty
			while (m_Queue.size() > 0)
			{
				//Sound
				{
					// Load the oldest object in the Queue
					std::scoped_lock lock(m_SoundEffectsMutex);
					auto temp = m_Queue.front();
					// Unlock lock
				}

				Load(m_Queue.front());

				// If the sound is loaded, play it
				if (m_pSoundEffects.count(m_Queue.front().name))
				{
					// Play the sound
					PlaySoundEffect(m_Queue.front());

					// Remove the sound from the queue
					m_Queue.pop();
				}
			}
		}
	}

	void PushOnQueue(Sound audio)
	{
		m_Queue.push(audio);
	}

	void Cleanup()
	{
		m_IsActive = false;

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
	pImpl->PlaySoundEffect(audio);
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
	m_Thread = std::jthread(&dae::SDLSoundSystem::CheckQueue, this);
}

void dae::SDLSoundSystem::PlaySoundEffect(Sound audio)
{
	pImpl->PlaySoundEffect(audio);
}

void dae::SDLSoundSystem::PlayMusic(Sound music)
{
	pImpl->PlayMusic(music);
}

void dae::SDLSoundSystem::PauseSoundEffects()
{
	pImpl->PauseSoundEffects();
}

void dae::SDLSoundSystem::PauseMusic()
{
	pImpl->PauseMusic();
}

void dae::SDLSoundSystem::ResumeSoundEffects()
{
	pImpl->ResumeSoundEffects();
}

void dae::SDLSoundSystem::ResumeMusic()
{
	pImpl->ResumeMusic();
}

void dae::SDLSoundSystem::CheckQueue()
{
	pImpl->CheckQueue();
}

void dae::SDLSoundSystem::PushOnQueue(Sound audio)
{
	pImpl->PushOnQueue(audio);
}

void dae::SDLSoundSystem::StopSoundEffects()
{
	pImpl->StopSoundEffects();
}

void dae::SDLSoundSystem::StopMusic()
{
	pImpl->StopMusic();
}

void dae::SDLSoundSystem::Load(Sound audio)
{
	pImpl->Load(audio);
}

bool dae::SDLSoundSystem::ToggleMute()
{
	return pImpl->ToggleMute();
}

void dae::SDLSoundSystem::SetSoundEffectVolume(float volume)
{
	pImpl->SetSoundEffectVolume(volume);
}

void dae::SDLSoundSystem::SetMusicVolume(float volume)
{
	pImpl->SetMusicVolume(volume);
}

dae::SDLSoundSystem::~SDLSoundSystem()
{
	pImpl->Cleanup();
	m_Thread.join();

	delete pImpl;
	pImpl = nullptr;
}