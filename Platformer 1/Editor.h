#pragma once
#include <allegro5/allegro.h>
class Editor
{
public:
	Editor(void);
	~Editor(void);

	static Editor& GI();

	void Update();
	void Draw();

	enum Objects
	{
		wall						= 0,
		spike_up					= 1,
		spike_down					= 2,
		spike_left					= 3,
		spike_right					= 4,
		wall_fade					= 5,
		wall_fake					= 6,
		obj_double_spike_trigger	= 7,
		obj_saw						= 8,
		obj_saw_small				= 9,
		obj_saw_bar					= 10,
		obj_platform_vertical		= 11,
		obj_platform_horizontal		= 12,
		obj_treadmill_left_begin	= 13,
		obj_treadmill_left			= 14,
		obj_treadmill_left_end		= 15,
		obj_treadmill_right_begin	= 16,
		obj_treadmill_right			= 17,
		obj_treadmill_right_end		= 18,
		save_pussy					= 19,
		save_medium					= 20,
		save_hard					= 21,
		player						= 22,
		LAST_OBJECT
	};

private:
	void CreateObject();
	void DeleteObject();

	void NextObject();
	void PreviousObject();

	void SetSelectedObject(int object);

	int selectedObject;

	ALLEGRO_BITMAP *objImage;
};

