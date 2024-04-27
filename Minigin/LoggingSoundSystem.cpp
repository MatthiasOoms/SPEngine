#include "LoggingSoundSystem.h"

dae::LoggingSoundSystem::LoggingSoundSystem(std::unique_ptr<SoundSystem>&& ss)
{
	_real_ss = (std::move(ss));
	std::cout << "Creating Logging Sound System" << std::endl;
}

void dae::LoggingSoundSystem::Play(const sound_id id, const float volume)
{
	_real_ss->Play(id, volume);
	std::cout << "Playing " << id << " at volume " << volume << std::endl;
}

void dae::LoggingSoundSystem::Pause()
{
	_real_ss->Pause();
	std::cout << "Pausing sounds" << std::endl;

}

void dae::LoggingSoundSystem::Resume()
{
	_real_ss->Resume();
	std::cout << "Resuming sounds" << std::endl;
}

void dae::LoggingSoundSystem::Stop()
{
	_real_ss->Stop();
	std::cout << "Stopping sounds" << std::endl;
}

void dae::LoggingSoundSystem::Load(const std::string& filePath)
{
	_real_ss->Load(filePath);
	std::cout << "Loading " << filePath << std::endl;
}