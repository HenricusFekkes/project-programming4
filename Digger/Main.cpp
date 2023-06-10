#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "LoggingAudioService.h"
#include "Minigin.h"
#include "SceneLoaders.h"
#include "AudioService.h"
#include "ServiceLocator.h"

using namespace dae;

int main(int, char* [])
{
	ServiceLocator::GetInstance().Initialize();
	IAudioService* ss = new LoggingAudioService(new AudioService());
	ServiceLocator::GetInstance().RegisterSoundService(ss);

	Minigin engine("../Data/");
	engine.Run(LoadAudioScene);


	delete ss;
	return 0;
}