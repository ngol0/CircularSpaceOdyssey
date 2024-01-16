#include "stdafx.h"
#include "AudioManager.h"

AudioManager::AudioManager() {}

void AudioManager::Init()
{
	//init sound effects map
	sound_effects[SoundID::ENEMY_EXPLODE] = ".\\Data\\Sound\\Explosion2__006.wav";
	sound_effects[SoundID::PLAYER_EXPLODE] = ".\\Data\\Sound\\Explosion2__004.wav";
	sound_effects[SoundID::HEALTH_POWER] = ".\\Data\\Sound\\Pickup__008.wav";
	sound_effects[SoundID::PLAYER_SHOOT] = ".\\Data\\Sound\\pew-shot.wav";
	sound_effects[SoundID::ENEMY_SHOOT] = ".\\Data\\Sound\\Bass Drum__008.wav";
	sound_effects[SoundID::PLAYER_DAMAGED] = ".\\Data\\Sound\\hit.wav";
	sound_effects[SoundID::BUTTON] = ".\\Data\\Sound\\select-granted-04.wav";

	//init music map
	music[MusicID::IN_GAME] = ".\\Data\\Sound\\Drum_Loop.wav";
}

void AudioManager::PlaySoundEffect(const std::string& id, bool looping)
{
	if (sound_effects[id] == NULL) return;
	App::PlaySound(sound_effects[id], looping);
}

void AudioManager::PlayMusic(const std::string& id, bool looping)
{
	if (music[id] == NULL) return;
	App::PlaySound(music[id], looping);
}

void AudioManager::StopMusic(const std::string& id)
{
	if (music[id] == NULL) return;
	App::StopSound(music[id]);
}

AudioManager& AudioManager::GetInstance()
{
	static AudioManager manager;
	return manager;
}


