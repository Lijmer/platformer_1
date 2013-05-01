#ifndef GLOBALS_H
#define GLOBALS_H

const float PI = (float)3.141592;

const int _SCREEN_WIDTH = 1024;
const int _SCREEN_HEIGHT = 768;

enum _OBJECT_ID
{
	UNDEFINED=-1,
	PLAYER=0,
	WALL=1,
	SPIKE=2,
	SAW=3,
	WALL_FADE = 5,
	WALL_FAKE=6,
	TRIGGER_DOUBLE_SPIKE=7,
	VERTICAL_PLATFORM,
	HORIZONTAL_PLATFORM,
	TREADMILL_LEFT,
	TREADMILL_RIGHT,
	SAVE,
	BULLET,
	PARTICLE
};

enum COLLISION_TYPE{
	BB,		// = Bounding Box
	TBB,	// = Triangle Bounding Box
	CBB,	// = Circle Bounding Box
	PPC		// = Pixel Perfect Collision
};

enum _KEYS
{
	UP=0,
	DOWN,
	LEFT,
	RIGHT,
	SPACE,
	Z_KEY,
	X_KEY,
	R_KEY,
	ALT
};

enum SND
{
	SHOOT,
	JUMP1,
	JUMP2,
	SPLAT
};

enum _DIFFICULTY
{
	EASY=0,
	MEDIUM,
	HARD,
	IMPOSSIBLE
};


extern float _monitorWidth, _monitorHeight, _scaleScreen;

extern int _camX, _camY, _camX_prev, _camY_prev;
extern int _difficulty, _currentLevel, _saveNum;
extern bool _keys[], _keys_pressed[], _keys_released[];
extern int _hours, _minutes, _seconds, _steps;
extern int _deaths;

#endif