#pragma once
#include "Mof.h"
#include "Common.h"

class CWindowUtillities
{
public:

	CWindowUtillities(void) = delete;

	~CWindowUtillities(void) = delete;

	static void ToggleTitleBarEnable(void);

	static void SetForeGround(const bool& b);

	static WINDOWSIZE GetWindowSize(void);

};

