#pragma once
#include <string>
#include <memory>

namespace dae {

	class Sound;
	class IAudioService
	{
	public:
		virtual ~IAudioService() = default;

		virtual void Play(std::shared_ptr<Sound>& sound, int volume) = 0;
	};
}