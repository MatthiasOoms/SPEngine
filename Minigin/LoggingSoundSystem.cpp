#include "LoggingSoundSystem.h"

dae::LoggingSoundSystem::LoggingSoundSystem(std::unique_ptr<SoundSystem>&& ss)
{
	_real_ss = (std::move(ss));
	std::cout << "Creating Logging Sound System" << std::endl;
}

void dae::LoggingSoundSystem::Play(const sound_name name, const float volume)
{
	_real_ss->Play(name, volume);
	std::cout << "Playing " << name << " at volume " << volume << std::endl;
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

bool dae::LoggingSoundSystem::Load(const std::string& filePath)
{
	std::cout << "Loading " << filePath << ": ";
	if (_real_ss->Load(filePath))
	{
		std::cout << "Succeded " << std::endl;
		return true;
	}
	else
	{
		std::cout << "Failed " << std::endl;
		return false;
	}
}