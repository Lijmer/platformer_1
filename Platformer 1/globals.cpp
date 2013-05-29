#include "globals.h"
int _camX = 0, _camY=0, _camX_prev=-1, _camY_prev=-1;
int _difficulty = 0, _currentLevel=0;
int _hours=0, _minutes=0, _seconds=0, _steps=0;
int _deaths=0;

float _monitorWidth = 0, _monitorHeight = 0, _scaleScreen;

bool _keys_pressed[KEYS_SIZE]		=	{false, false, false, false, false, false, false, false, false, false, false, false, false, false};
bool _keys_released[KEYS_SIZE]		=	{false, false, false, false, false, false, false, false, false, false, false, false, false, false};
bool _keys[KEYS_SIZE]				=	{false, false, false, false, false, false, false, false, false, false, false, false, false, false};
bool _mouse[M_SIZE]					=	{false, false};
bool _mouse_pressed[M_SIZE]			=	{false, false};
bool _mouse_released[M_SIZE]		=	{false, false};

float _mouseX = 0;
float _mouseY = 0;