/*This class manages all the audios in the game
* The responsibility of this class is to:
** Init a map of id and file name
** Play sound or music based on the pre-stated id
*/
#pragma once
#include <map>

namespace SoundID
{
	const static std::string ENEMY_EXPLODE = "enemy_explode";
	const static std::string PLAYER_EXPLODE = "player_explode";
	const static std::string HEALTH_POWER = "health_power";
	const static std::string ENEMY_SHOOT = "enemy_shoot";
	const static std::string PLAYER_SHOOT = "player_shoot";
	const static std::string PLAYER_DAMAGED = "player_damaged";
	const static std::string BUTTON = "game_start";
}

namespace MusicID
{
	const static std::string IN_GAME = "in_game";
	const static std::string OUT_GAME = "out_game";
}

class AudioManager
{
public:
	AudioManager();
	AudioManager(const AudioManager&) = delete; //avoid copy constructor

	void Init();
	void PlaySoundEffect(const std::string& id, bool looping);
	void PlayMusic(const std::string& id, bool looping);
	void StopMusic(const std::string& id);

	//singleton
	static AudioManager& GetInstance();

private:
	std::map<std::string, const char*> sound_effects;
	std::map<std::string, const char*> music;
};
