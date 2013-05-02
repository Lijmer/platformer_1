#pragma once
#include <allegro5/allegro.h>


class ImageManager
{
public:
	ImageManager(void);
	~ImageManager(void);
		
	static ImageManager &GetInstance();

	void Init();
	void Load();

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
	ALLEGRO_BITMAP *img_platform;
	ALLEGRO_BITMAP *img_treadmill_begin;
	ALLEGRO_BITMAP *img_treadmill;
	ALLEGRO_BITMAP *img_treadmill_end;
	
	ALLEGRO_BITMAP *img_blood;
	ALLEGRO_BITMAP *img_blood_head;
	ALLEGRO_BITMAP *img_blood_torso;
	ALLEGRO_BITMAP *img_blood_arm;
	ALLEGRO_BITMAP *img_blood_foot;
};

