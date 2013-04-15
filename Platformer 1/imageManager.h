#pragma once
#include "globals.h"
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
class ImageManager
{
public:
	ImageManager(void);
	~ImageManager(void);
		
	static ImageManager &GetInstance();

	void Init();
	void Load();
	void Clean();

	ALLEGRO_BITMAP* GetImage(char ID = -1);

private:
	ALLEGRO_BITMAP *img_player;
	ALLEGRO_BITMAP *img_wall;
	ALLEGRO_BITMAP *img_spike_up;
	ALLEGRO_BITMAP *img_spike_down;
	ALLEGRO_BITMAP *img_spike_left;
	ALLEGRO_BITMAP *img_spike_right;
	ALLEGRO_BITMAP *img_save;
	ALLEGRO_BITMAP *img_saw;
	ALLEGRO_BITMAP *img_saw_bar;
	
	ALLEGRO_BITMAP *img_blood;
	ALLEGRO_BITMAP *img_blood_head;
	ALLEGRO_BITMAP *img_blood_torso;
	ALLEGRO_BITMAP *img_blood_arm;
	ALLEGRO_BITMAP *img_blood_foot;
};

