#pragma once

#include <allegro5\allegro.h>
#include <allegro5\keyboard.h>
#include <vector>

using std::vector;

class InputManager
{
private:
	ALLEGRO_KEYBOARD_STATE keyState;

public:
	InputManager(void);
	~InputManager(void);

	bool isKeyPressed(ALLEGRO_EVENT ev, int key);
	bool isKeyPressed(ALLEGRO_EVENT ev, vector<int> keys);

	bool isKeyReleased(ALLEGRO_EVENT ev, int key);
	bool isKeyReleased(ALLEGRO_EVENT ev, vector<int> keys);
};

