#pragma once
#include "Command.h"

struct WaitCommand : public Command
{
	void execute() override;
};