#include "NullAudioService.h"

using namespace dae;

void NullAudioService::Play(sound_id, int) {}
sound_id NullAudioService::Load(const std::string&) { return 0; };