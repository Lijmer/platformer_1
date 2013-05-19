#ifndef EXIT_H
#define EXIT_H
namespace Exit
{
	extern void ExitProgram(int returnValue=0);
	extern bool GetDone();
	extern int GetReturnValue();
}
#endif