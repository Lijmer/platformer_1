#include "imageManager.h"


ImageManager::ImageManager(void)
{
}


ImageManager::~ImageManager(void)
{
	al_destroy_bitmap(img_player);
	al_destroy_bitmap(img_wall);
	al_destroy_bitmap(img_spike_up);
	al_destroy_bitmap(img_spike_down);
	al_destroy_bitmap(img_spike_left);
	al_destroy_bitmap(img_spike_right);
	al_destroy_bitmap(img_save);
	al_destroy_bitmap(img_saw);
	al_destroy_bitmap(img_saw_bar);
	al_destroy_bitmap(img_platform);
	al_destroy_bitmap(img_treadmill_begin);
	al_destroy_bitmap(img_treadmill);
	al_destroy_bitmap(img_treadmill_end);

	al_destroy_bitmap(img_blood);
	al_destroy_bitmap(img_blood_head);
	al_destroy_bitmap(img_blood_torso);
	al_destroy_bitmap(img_blood_arm);
	al_destroy_bitmap(img_blood_foot);
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
	img_player = al_load_bitmap("img/player/sprite_sheet.png");
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

	std::string error = "";

	//Check if all the images are loadeds
	if(img_player==NULL)
		error = "img_player";
	else if(img_wall==NULL)
		error = "img_wall";
	else if(img_spike_up == NULL)
		error = "img_spike_up";
	else if(img_spike_down == NULL)
		error = "img_spike_down";
	else if(img_spike_left == NULL)
		error = "img_spike_left";
	else if(img_spike_right == NULL)
		error = "img_spike_right";
	else if(img_save == NULL)
		error = "img_save";
	else if(img_saw == NULL)
		error = "img_saw";
	else if(img_saw_bar == NULL)
		error = "img_saw_bar";
	else if(img_platform == NULL)
		error = "img_platform";
	else if(img_treadmill_begin == NULL)
		error = "img_treadmill_begin";
	else if(img_treadmill == NULL)
		error = "img_treadmill";
	else if(img_treadmill_end == NULL)
		error = "img_treadmill_end";
	else if(img_blood == NULL)
		error = "img_blood";

	else if(img_blood_head == NULL)
		error = "img_blood_head";
	else if(img_blood_torso == NULL)
		error = "img_blood_torso";
	else if(img_blood_arm == NULL)
		error = "img_blood_arm";
	else if(img_blood_foot == NULL)
		error = "img_blood_foot";

	if(error != "")
	{
		std::string finalErrorMessage = "Couldn't load " + error + ".";
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "Error!", "ImageManager", finalErrorMessage.c_str(), "ok", ALLEGRO_MESSAGEBOX_ERROR);
	}
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
	case 2:
		return img_wall;
		break;
	case 3:
		return img_spike_up;
		break;
	case 4:
		return img_spike_down;
		break;
	case 5:
		return img_spike_left;
		break;
	case 6:
		return img_spike_right;
		break;
	case 7:
		return img_save;
		break;
	case 8:
		return img_saw;
		break;
	case 9:
		return img_saw_bar;
		break;
	case 10:
		return img_platform;
		break;
	case 11:
		return img_treadmill_begin;
		break;
	case 12:
		return img_treadmill;
		break;
	case 13:
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