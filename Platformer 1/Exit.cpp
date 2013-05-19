#include "Exit.h"
#include <iostream>
static bool done = false;
//This value will get returned by main when the program exits
static int returnValue = 0;

namespace Exit
{
	void ExitProgram(int returnValue)
	{
		::returnValue = returnValue;
		done = true;
	}
	inline bool GetDone()
	{
		return done;
	}
	int GetReturnValue()
	{
		return returnValue;
	}
}