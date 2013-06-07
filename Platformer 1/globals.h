#ifndef GLOBALS_H
#define GLOBALS_H

const float PI = (float)3.141592;
const float TAU = (float)6.283184;

const int _SCREEN_WIDTH = 1024;
const int _SCREEN_HEIGHT = 768;

extern bool GetDropFrames();
extern void ToggleDropFrames();
extern void SetDropFrames(bool drop);
extern void CheckIfCamIsChanged();
extern void OverrideCamChanged(bool changed);
extern bool GetCamChanged();

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
	UP,
	DOWN,
	LEFT,
	RIGHT,
	SPACE,
	L_KEY,
	M_KEY,
	Q_KEY,
	R_KEY,
	S_KEY,
	X_KEY,
	Z_KEY,
	ENTER,
	ALT,
	ALTGR,
	ESCAPE,
	KEYS_SIZE
};
enum MOUSE
{
	M_LEFT,
	M_RIGHT,
	M_SIZE
};

enum DIFFICULTY
{
	EASY=0,
	MEDIUM,
	HARD,
	IMPOSSIBLE
};


extern float _monitorWidth, _monitorHeight, _scaleScreen;

extern int _camX, _camY, _camX_prev, _camY_prev;
extern int _difficulty, _currentLevel;
extern bool _keys[KEYS_SIZE], _keys_pressed[KEYS_SIZE], _keys_released[KEYS_SIZE];
extern bool _mouse[M_SIZE], _mouse_pressed[M_SIZE], _mouse_released[M_SIZE];
extern float _mouseX, _mouseY;
extern int _hours, _minutes, _seconds, _steps;
extern int _deaths;

#endif