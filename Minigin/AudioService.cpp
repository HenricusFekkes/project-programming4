#include "AudioService.h"

#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <SDL.h>
#include <SDL_mixer.h>
#include <thread>

#include "Sound.h"

using namespace dae;

class AudioService::AudioServiceImpl final
{
	struct Task
	{
		Task(std::shared_ptr<Sound>& sound, int volume)
			: Sound{ sound }, Volume{ volume }
		{}

		void Process() const
		{
			Mix_VolumeChunk(Sound->GetSDLChunk(), Volume);
			Mix_PlayChannel(-1, Sound->GetSDLChunk(), 0);
		}

		const std::shared_ptr<Sound> Sound;
		const int Volume;
	};

public:
	AudioServiceImpl()
	{
		if (SDL_Init(SDL_INIT_AUDIO) != 0) {
			throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
		}
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
			std::cerr << "SDL2 mixer initialization failed: " << Mix_GetError() << std::endl;
			throw std::runtime_error("SDL2 mixer initialization failed");
		}

		m_IsRunning = true;
		m_Thread = std::jthread(std::bind(&AudioServiceImpl::ProcessTaskQueue, this));
	}

	~AudioServiceImpl()
	{
		m_IsRunning = false;
		m_Condition.notify_all();
		Mix_CloseAudio();
	}

	void ProcessTaskQueue()
	{
		while (m_IsRunning)
		{
			auto lock = std::unique_lock(m_QueueMutex);
			m_Condition.wait(lock, [&]() { return not m_IsRunning or not m_TaskQueue.empty(); });
			if(not m_IsRunning)
			{
				return;
			}

			if(not m_TaskQueue.empty())
			{
				Task task = m_TaskQueue.front();
				m_TaskQueue.pop();
				lock.unlock();

				task.Process();
			}
		}
	}

	void Play(std::shared_ptr<Sound>& sound, int volume)
	{
		m_QueueMutex.lock();
		m_TaskQueue.emplace(sound, volume);
		m_QueueMutex.unlock();
		m_Condition.notify_all();
	}

private:
	std::jthread m_Thread;
	std::queue<Task> m_TaskQueue{};
	std::mutex m_QueueMutex{};
	std::condition_variable m_Condition{};
	bool m_IsRunning{};
};

AudioService::AudioService()
{
	pImpl = new AudioServiceImpl();
}

AudioService::~AudioService()
{
	delete pImpl;
}

void AudioService::Play(std::shared_ptr<Sound>& sound, int volume)
{
	pImpl->Play(sound, volume);
}


