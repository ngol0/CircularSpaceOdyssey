#include "stdafx.h"
#include "AudioManager.h"

AudioManager::AudioManager() {}

void AudioManager::Init()
{
	//init sound effects map
	sound_effects["enemy_explode"] = ".\\Data\\Sound\\Explosion2__006.wav";
	sound_effects["player_explode"] = ".\\Data\\Sound\\Explosion2__004.wav";
	sound_effects["power"] = ".\\Data\\Sound\\Pickup__008.wav";
	sound_effects["player_shoot"] = ".\\Data\\Sound\\Bass Drum__003.wav";
	sound_effects["enemy_shoot"] = ".\\Data\\Sound\\Bass Drum__008.wav";
	sound_effects["player_damaged"] = ".\\Data\\Sound\\hit.wav";
	sound_effects["game_start"] = ".\\Data\\Sound\\select-granted-04.wav";

	//init music map

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

AudioManager& AudioManager::GetInstance()
{
	static AudioManager manager;
	return manager;
}


