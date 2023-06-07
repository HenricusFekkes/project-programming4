#include "NullSoundService.h"

using namespace dae;

void NullSoundService::Play(sound_id, int) {}
sound_id NullSoundService::Load(const std::string&) { return 0; };