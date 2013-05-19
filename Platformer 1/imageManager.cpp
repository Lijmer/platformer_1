#include "imageManager.h"

#include "DisplayManager.h"
#include "FileManager.h"

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include "globals.h"
#include <string>
#include <sstream>
#include <vector>

#include "exit.h"

ImageManager::ImageManager(void)
{
}


ImageManager::~ImageManager(void)
{
	DestroyAllImages();
}


ImageManager &ImageManager::GetInstance()
{
	static ImageManager instance;
	return instance;
}

void ImageManager::Init()
{
	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
	al_init_image_addon();
	/*img_player = al_load_bitmap("img/player/sprite_sheet.png");
	img_wall = al_load_bitmap("img/tiles/32x32/wall.png");
	img_spike_up = al_load_bitmap("img/tiles/32x32/spike_up.png");
	img_spike_down = al_load_bitmap("img/tiles/32x32/spike_down.png");
	img_spike_left = al_load_bitmap("img/tiles/32x32/spike_left.png");
	img_spike_right = al_load_bitmap("img/tiles/32x32/spike_right.png");
	img_save = al_load_bitmap("img/tiles/other/save.png");
	img_saw = al_load_bitmap("img/tiles/128x128/saw.png");
	img_saw_bar = al_load_bitmap("img/other/saw_bar.png");
	img_platform = al_load_bitmap("img/tiles/other/platform.png");
	img_treadmill_begin = al_load_bitmap("img/tiles/32x32/treadmill_begin.png");
	img_treadmill = al_load_bitmap("img/tiles/32x32/treadmill.png");
	img_treadmill_end = al_load_bitmap("img/tiles/32x32/treadmill_end.png");
	
	img_blood = al_load_bitmap("img/player/blood/blood_pixel.png");
	img_blood_head = al_load_bitmap("img/player/blood/head.png");
	img_blood_torso = al_load_bitmap("img/player/blood/torso.png");
	img_blood_arm = al_load_bitmap("img/player/blood/arm.png");
	img_blood_foot = al_load_bitmap("img/player/blood/foot.png");

	//std::string error = "";

	try
	{
		if(img_player==NULL)
			throw "img_player";
		else if(img_wall==NULL)
			throw "img_wall";
		else if(img_spike_up == NULL)
			throw "img_spike_up";
		else if(img_spike_down == NULL)
			throw "img_spike_down";
		else if(img_spike_left == NULL)
			throw "img_spike_left";
		else if(img_spike_right == NULL)
			throw "img_spike_right";
		else if(img_save == NULL)
			throw "img_save";
		else if(img_saw == NULL)
			throw "img_saw";
		else if(img_saw_bar == NULL)
			throw "img_saw_bar";
		else if(img_platform == NULL)
			throw "img_platform";
		else if(img_treadmill_begin == NULL)
			throw "img_treadmill_begin";
		else if(img_treadmill == NULL)
			throw "img_treadmill";
		else if(img_treadmill_end == NULL)
			throw "img_treadmill_end";
		else if(img_blood == NULL)
			throw "img_blood";

		else if(img_blood_head == NULL)
			throw "img_blood_head";
		else if(img_blood_torso == NULL)
			throw "img_blood_torso";
		else if(img_blood_arm == NULL)
			throw "img_blood_arm";
		else if(img_blood_foot == NULL)
			throw "img_blood_foot";
	}catch(char const* error)
	{
		std::stringstream finalErrorMessage;
		finalErrorMessage << "Couldn't load " << error << ".";
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "Error!", "ImageManager", finalErrorMessage.str().c_str(), "ok", ALLEGRO_MESSAGEBOX_ERROR);
		Exit::ExitProgram(-1);
	}*/
}


ALLEGRO_BITMAP* ImageManager::GetImage(char ID)
{
	switch(ID)
	{
	case -1:
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "Error!", "ImageManager", "-1 passed into image manager", "", 0);
		break;
	case 0:
		return img_player;
		break;
	case 1:
		return img_wall;
		break;
	case 2:
		return img_spike_up;
		break;
	case 3:
		return img_spike_down;
		break;
	case 4:
		return img_spike_left;
		break;
	case 5:
		return img_spike_right;
		break;
	case 6:
		return img_save;
		break;
	case 7:
		return img_saw;
		break;
	case 8:
		return img_saw_bar;
		break;
	case 9:
		return img_platform;
		break;
	case 10:
		return img_treadmill_begin;
		break;
	case 11:
		return img_treadmill;
		break;
	case 12:
		return img_treadmill_end;
		break;
	case 100:
		return img_blood;
		break;
	case 101:
		return img_blood_head;
		break;
	case 102:
		return img_blood_torso;
		break;
	case 103:
		return img_blood_arm;
		break;
	case 104:
		return img_blood_foot;
		break;
	}
	al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "Error!", "ImageManager", "NULL or unknown value passed into image manager", "", 0);
	return NULL;
}

void ImageManager::LoadImages(int currentLevel)
{
	DestroyAllImages();
	std::vector<int> imgNums = FileManager::GetInstance().LoadImageNums(currentLevel);
	std::vector<int>::iterator iter;

	for(iter = imgNums.begin(); iter!=imgNums.end(); iter++)
	{
		try
		{
			switch(*iter)
			{
			case 0:
				img_player = al_load_bitmap("img/player/sprite_sheet.png");
				if(img_player == NULL)
					throw "img_player";
				img_blood_head = al_load_bitmap("img/player/blood/head.png");
				if(img_blood_head == NULL)
					throw "img_blood_head";
				img_blood_torso = al_load_bitmap("img/player/blood/torso.png");
				if(img_blood_torso == NULL)
					throw "img_blood_torso";
				img_blood_arm = al_load_bitmap("img/player/blood/arm.png");
				if(img_blood_arm == NULL)
					throw "img_blood_arm";
				//img_blood_foot = al_load_bitmap("img/player/blood/foot.png");
				//if(img_blood_foot == NULL);
					//throw "img_blood_foot";
				break;
			case 1:
				img_wall = al_load_bitmap("img/tiles/32x32/wall.png");
				if(img_wall==NULL)
					throw "img_wall";
				break;
			case 2:
				img_spike_up = al_load_bitmap("img/tiles/32x32/spike_up.png");
				if(img_spike_up == NULL)
					throw "img_spike_up";
				break;
			case 3:
				img_spike_down = al_load_bitmap("img/tiles/32x32/spike_down.png");
				if(img_spike_down == NULL)
					throw "img_spike_down";
				break;
			case 4:
				img_spike_left = al_load_bitmap("img/tiles/32x32/spike_left.png");
				if(img_spike_left == NULL)
					throw "img_spike_left";
				break;
			case 5:
				img_spike_right = al_load_bitmap("img/tiles/32x32/spike_right.png");
				if(img_spike_right == NULL)
					throw "img_spike_right";
				break;
			case 6:
				img_save = al_load_bitmap("img/tiles/other/save.png");
				if(img_save == NULL)
					throw "img_save";
				break;
			case 7:
				img_saw = al_load_bitmap("img/tiles/128x128/saw.png");
				if(img_saw == NULL)
					throw "img_saw";
				break;
			case 8:
				img_saw_bar = al_load_bitmap("img/other/saw_bar.png");
				if(img_saw_bar == NULL)
					throw "img_saw_bar";
				break;
			case 9:
				img_platform = al_load_bitmap("img/tiles/other/platform.png");
				if(img_platform == NULL)
					throw "img_platform";
				break;
			case 10:
				img_treadmill_begin = al_load_bitmap("img/tiles/32x32/treadmill_begin.png");
				if(img_treadmill_begin == NULL)
					throw "img_treadmill_begin";
				break;
			case 11:
				img_treadmill = al_load_bitmap("img/tiles/32x32/treadmill.png");
				if(img_treadmill == NULL)
					throw "img_treadmill";
				break;
			case 12:
				img_treadmill_end = al_load_bitmap("img/tiles/32x32/treadmill_end.png");
				if(img_treadmill_end == NULL)
					throw "img_treadmill_end";
				break;
			}
		}
		catch(char const* error)
		{
			std::stringstream finalErrorMessage;
			finalErrorMessage << "Couldn't load " << error << ".";
			al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "Error!", "ImageManager", finalErrorMessage.str().c_str(), "ok", ALLEGRO_MESSAGEBOX_ERROR);
			Exit::ExitProgram(-10);
		}
	}
}

inline void ImageManager::DestroyAllImages()
{
	if(img_player)
		al_destroy_bitmap(img_player);
	if(img_wall)
		al_destroy_bitmap(img_wall);
	if(img_spike_up)
		al_destroy_bitmap(img_spike_up);
	if(img_spike_down)
		al_destroy_bitmap(img_spike_down);
	if(img_spike_left)
		al_destroy_bitmap(img_spike_left);
	if(img_spike_right)
		al_destroy_bitmap(img_spike_right);
	if(img_save)
		al_destroy_bitmap(img_save);
	if(img_saw)
		al_destroy_bitmap(img_saw);
	if(img_saw_bar)
		al_destroy_bitmap(img_saw_bar);
	if(img_platform)
		al_destroy_bitmap(img_platform);
	if(img_treadmill_begin)
		al_destroy_bitmap(img_treadmill_begin);
	if(img_treadmill)
		al_destroy_bitmap(img_treadmill);
	if(img_treadmill_end)
		al_destroy_bitmap(img_treadmill_end);

	if(img_blood)
		al_destroy_bitmap(img_blood);
	if(img_blood_head)
		al_destroy_bitmap(img_blood_head);
	if(img_blood_torso)
		al_destroy_bitmap(img_blood_torso);
	if(img_blood_arm)
		al_destroy_bitmap(img_blood_arm);
	if(img_blood_foot)
		al_destroy_bitmap(img_blood_foot);
}