#pragma once
#include "Command.h"

enum class EnemyType;

struct SpawnCommand : public Command
{
	int id;
	float spawn_time;

	SpawnCommand(EnemyType type, float time);

	void execute() override;
};