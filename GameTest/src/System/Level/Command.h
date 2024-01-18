#pragma once

struct Command
{
	virtual ~Command() {};
	virtual void execute() = 0;
};