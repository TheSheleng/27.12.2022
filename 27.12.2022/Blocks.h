#pragma once
#include "Creature.h"

struct Block
{
	virtual float OvercomeBy(const Member&) = 0;
};

class Wall : public Block
{
	const float HEIGHT;

public:
	Wall(const float _h) : HEIGHT(_h) {};
	float OvercomeBy (const Member& _being) override
	{
		return (float)HEIGHT / _being.Climb();
	}
};

class Track : public Block
{
	const unsigned LENGTH;

public:
	Track(const unsigned _l) : LENGTH(_l) {};
	float OvercomeBy(const Member& _being) override
	{
		return (float)LENGTH / _being.Run();
	}
};