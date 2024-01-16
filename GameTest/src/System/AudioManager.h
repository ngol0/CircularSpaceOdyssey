#pragma once
#include <map>

class AudioManager
{
public:
	AudioManager();
	AudioManager(const AudioManager&) = delete; //avoid copy constructor

	void Init();
	void PlaySoundEffect(const std::string& id, bool looping);
	void PlayMusic(const std::string& id, bool looping);

	//singleton
	static AudioManager& GetInstance();

private:
	std::map<std::string, const char*> sound_effects;
	std::map<std::string, const char*> music;
};
