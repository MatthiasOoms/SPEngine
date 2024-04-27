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

void dae::LoggingSoundSystem::Play(Sound audio)
{
	_real_ss->Play(audio);
	std::cout << "Playing " << audio.name << " at volume " << audio.volume << std::endl;
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

void dae::LoggingSoundSystem::CheckQueue()
{
	_real_ss->CheckQueue();
	// Do not print since it happens every frame
	//std::cout << "Checking sound queue" << std::endl;
}

void dae::LoggingSoundSystem::PushOnQueue(Sound audio)
{
	_real_ss->PushOnQueue(audio);
	std::cout << "Pushing sound on queue" << std::endl;
}

void dae::LoggingSoundSystem::Stop()
{
	_real_ss->Stop();
	std::cout << "Stopping sounds" << std::endl;
}

bool dae::LoggingSoundSystem::Load(Sound audio)
{
	std::cout << "Loading " << audio.filePath << ": ";
	if (_real_ss->Load(audio))
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