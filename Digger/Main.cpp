#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "LoggingSoundService.h"
#include "Minigin.h"
#include "SceneLoaders.h"
#include "SdlSoundService.h"
#include "ServiceLocator.h"

using namespace dae;

int main(int, char* [])
{
	ServiceLocator::Initialize();
	SoundService* ss = new LoggingSoundService(new SdlSoundService());
	ServiceLocator::RegisterSoundService(ss);

	Minigin engine("../Data/");
	engine.Run(LoadAudioScene);


	delete ss;
	return 0;
}