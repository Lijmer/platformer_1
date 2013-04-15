#ifndef GLOBALS_H
#define GLOBALS_H

const float PI = (float)3.141592;

const int _SCREEN_WIDTH = 1024;
const int _SCREEN_HEIGHT = 768;

	

enum _OBJECT_ID {UNDEFINED=-1, PLAYER=0, WALL=1, SPIKE=2, SAW=3, WALL_FADE = 5, WALL_FAKE=6, TRIGGER_DOUBLE_SPIKE=7, SAVE, BULLET, PARTICLE};
enum _KEYS {UP=0, DOWN, LEFT, RIGHT, SPACE, Z_KEY, X_KEY, R_KEY};
enum _SND {SHOOT,JUMP1,JUMP2,SPLAT};
enum _DIFFICULTY{EASY=0, MEDIUM, HARD, IMPOSSIBLE};

extern int _camX, _camY, _camX_prev, _camY_prev;
extern char _difficulty, _currentLevel;
extern bool _keys[], _keys_pressed[], _keys_released[];

#endif