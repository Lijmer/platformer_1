#include "globals.h"
int _camX = 0, _camY=0, _camX_prev=-1, _camY_prev=-1;
int _difficulty = -1, _currentLevel=0, _saveNum=0;
int _hours=0, _minutes=0, _seconds=0, _steps=0;
int _deaths=0;

float _monitorWidth = 0, _monitorHeight = 0, _scaleScreen;

bool _keys_pressed[]		=	{false, false, false, false, false, false, false, false, false};
bool _keys_released[]	=	{false, false, false, false, false, false, false, false, false};
bool _keys[]				=	{false, false, false, false, false, false, false, false, false};