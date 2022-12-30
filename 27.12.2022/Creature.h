#pragma once

#include <Windows.h>
#include <string>

class Member
{
	const std::string NAME;
	const unsigned SPEED;
	const unsigned JUMPING;
	WORD col;

public:
	Member(const std::string& _n, const unsigned _s, const unsigned _j) : NAME(_n), SPEED(_s), JUMPING(_j) {}

	const std::string& GetName() const { return NAME; }
	const unsigned Climb() const { return JUMPING; }
	const unsigned Run() const { return SPEED; }

	void SetCol(WORD _c) { col = _c; }
	WORD GetCol() { return col; }
};