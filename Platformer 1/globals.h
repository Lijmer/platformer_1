#ifndef GLOBALS_H
#define GLOBALS_H
#include "SoundManager.h"


const float PI = (float)3.141592;

namespace global
{
	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGHT = 768;

	

	enum OBJECT_ID {UNDEFINED=-1, PLAYER=0, WALL=1, SPIKE=2, SAW=3, WALL_FADE = 5, WALL_FAKE=6, TRIGGER_DOUBLE_SPIKE=7, SAVE, BULLET, PARTICLE};
	enum KEYS {UP=0, DOWN, LEFT, RIGHT, SPACE, Z_KEY, X_KEY, R_KEY};
	enum SND {SHOOT,JUMP1,JUMP2,SPLAT};
	enum DIFFICULTY{EASY=0, MEDIUM, HARD, IMPOSSIBLE};

	extern int camX, camY, camX_prev, camY_prev;
	extern char difficulty, currentLevel;
};

#endif