#ifndef GLOBALS_H
#define GLOBALS_H

const float PI = (float)3.141592;

const int _SCREEN_WIDTH = 1024;
const int _SCREEN_HEIGHT = 768;

enum OBJECT_ID
{
	UNDEFINED=-1,
	PLAYER=0,
	WALL,
	SPIKE,
	SAW,
	WALL_FADE,
	WALL_FAKE,
	TRIGGER_DOUBLE_SPIKE,
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

enum KEYS
{
	UP=0,
	DOWN,
	LEFT,
	RIGHT,
	SPACE,
	L_KEY,
	Q_KEY,
	R_KEY,
	X_KEY,
	Z_KEY,
	ENTER,
	ALT,
	ALTGR
};

enum SND
{
	SHOOT,
	JUMP1,
	JUMP2,
	SPLAT
};

enum DIFFICULTY
{
	EASY=0,
	MEDIUM,
	HARD,
	IMPOSSIBLE
};

const int _KEYS_SIZE=13;

extern float _monitorWidth, _monitorHeight, _scaleScreen;

extern int _camX, _camY, _camX_prev, _camY_prev;
extern int _difficulty, _currentLevel, _saveNum;
extern bool _keys[_KEYS_SIZE], _keys_pressed[_KEYS_SIZE], _keys_released[_KEYS_SIZE];
extern int _hours, _minutes, _seconds, _steps;
extern int _deaths;

#endif