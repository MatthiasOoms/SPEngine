#include "LoggingSoundSystem.h"

void dae::LoggingSoundSystem::InternalPlay(Sound)
{
	// Unused
}

dae::LoggingSoundSystem::LoggingSoundSystem(std::unique_ptr<SoundSystem>&& ss)
{
	_real_ss = (std::move(ss));
	std::cout << "Creating Logging Sound System" << std::endl;
}

void dae::LoggingSoundSystem::PlaySoundEffect(Sound audio)
{
	_real_ss->PlaySoundEffect(audio);
	std::cout << "Playing " << audio.name << std::endl;
}

void dae::LoggingSoundSystem::PlayMusic(Sound music)
{
	_real_ss->PlayMusic(music);
	std::cout << "Playing music " << music.name << std::endl;
}

void dae::LoggingSoundSystem::PauseSoundEffects()
{
	_real_ss->PauseSoundEffects();
	std::cout << "Pausing sounds" << std::endl;
}

void dae::LoggingSoundSystem::PauseMusic()
{
	_real_ss->PauseMusic();
	std::cout << "Pausing music" << std::endl;
}

void dae::LoggingSoundSystem::ResumeSoundEffects()
{
	_real_ss->ResumeSoundEffects();
	std::cout << "Resuming sounds" << std::endl;
}

void dae::LoggingSoundSystem::ResumeMusic()
{
	_real_ss->ResumeMusic();
	std::cout << "Resuming music" << std::endl;
}

void dae::LoggingSoundSystem::PushOnQueue(Sound audio)
{
	_real_ss->PushOnQueue(audio);
	std::cout << "Pushing sound on queue" << std::endl;
}

void dae::LoggingSoundSystem::StopSoundEffects()
{
	_real_ss->StopSoundEffects();
	std::cout << "Stopping sounds" << std::endl;
}

void dae::LoggingSoundSystem::StopMusic()
{
	_real_ss->StopMusic();
	std::cout << "Stopping music" << std::endl;
}

void dae::LoggingSoundSystem::Load(Sound audio)
{
	_real_ss->Load(audio);
	std::cout << "Loading " << audio.filePath << ": ";
}

bool dae::LoggingSoundSystem::ToggleMute()
{
	std::cout << "Toggling mute" << std::endl;
	return _real_ss->ToggleMute();
}

void dae::LoggingSoundSystem::SetSoundEffectVolume(float volume)
{
	_real_ss->SetSoundEffectVolume(volume);
	std::cout << "Setting sound effect volume to " << volume << std::endl;
}

void dae::LoggingSoundSystem::SetMusicVolume(float volume)
{
	_real_ss->SetMusicVolume(volume);
	std::cout << "Setting music volume to " << volume << std::endl;
}
