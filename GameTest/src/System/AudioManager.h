#pragma once
#include <map>

class AudioManager
{
public:
	AudioManager();
	void LoadAllAudios();
	void Play(const char* id);

private:
	std::map<std::string, std::string> audio_map;
};
