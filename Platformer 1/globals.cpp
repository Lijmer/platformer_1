#include "globals.h"
int _camX = 0, _camY=0, _camX_prev=-1, _camY_prev=-1;
char _difficulty = -1, _currentLevel=0;

bool _keys_pressed[]		=	{false, false, false, false, false, false, false, false};
bool _keys_released[]	=	{false, false, false, false, false, false, false, false};
bool _keys[]				=	{false, false, false, false, false, false, false, false};