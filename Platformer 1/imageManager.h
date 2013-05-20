#pragma once
#include <allegro5/allegro.h>


class ImageManager
{
public:
	ImageManager(void);
	~ImageManager(void);
		
	static ImageManager &GetInstance();

	void LoadImages(int currentLevel);
	

	ALLEGRO_BITMAP* GetImage(char ID = -1);

	enum IMG
	{
		IMG_PLAYER=0,
		IMG_WALL=1,
		IMG_SPIKE_UP=2,
		IMG_SPIKE_DOWN=3,
		IMG_SPIKE_LEFT=4,
		IMG_SPIKE_RIGHT=5,
		IMG_SAVE=6,
		IMG_SAW=7,
		IMG_SAW_BAR=8,
		IMG_PLATFORM=9,
		IMG_TREADMILL_BEGIN=10,
		IMG_TREADMILL=11,
		IMG_TREADMILL_END=12,
		IMG_BLOOD=100,
		IMG_BLOOD_HEAD=101,
		IMG_BLOOD_TORSO=102,
		IMG_BLOOD_ARM=103,
		IMG_BLOOD_FOOT=104
	};

private:
	void DestroyAllImages();

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

	ALLEGRO_BITMAP *img_button;
};

