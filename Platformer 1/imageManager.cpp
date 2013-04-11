#include "imageManager.h"


ImageManager::ImageManager(void)
{
}


ImageManager::~ImageManager(void)
{
}


ImageManager &ImageManager::getInstance()
{
	static ImageManager instance;
	return instance;
}

void ImageManager::init()
{
	al_init_image_addon();
	img_player = al_load_bitmap("img/player/sprite_sheet.png");
	img_wall = al_load_bitmap("img/tiles/32x32/wall.png");
	img_spike_up = al_load_bitmap("img/tiles/32x32/spike_up.png");
	img_spike_down = al_load_bitmap("img/tiles/32x32/spike_down.png");
	img_spike_left = al_load_bitmap("img/tiles/32x32/spike_left.png");
	img_spike_right = al_load_bitmap("img/tiles/32x32/spike_right.png");
	img_save = al_load_bitmap("img/tiles/other/save.png");
	img_saw = al_load_bitmap("img/tiles/128x128/saw.png");
	img_saw_bar = al_load_bitmap("img/saw_bar.png");
	
	img_blood = al_load_bitmap("img/player/blood/blood.png");
	img_blood_head = al_load_bitmap("img/player/blood/head.png");
	img_blood_torso = al_load_bitmap("img/player/blood/torso.png");
	img_blood_arm = al_load_bitmap("img/player/blood/arm.png");
	img_blood_foot = al_load_bitmap("img/player/blood/foot.png");
}

void ImageManager::clean()
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

	al_destroy_bitmap(img_blood);
	al_destroy_bitmap(img_blood_head);
	al_destroy_bitmap(img_blood_torso);
	al_destroy_bitmap(img_blood_arm);
	al_destroy_bitmap(img_blood_foot);
}

ALLEGRO_BITMAP* ImageManager::getImage(char ID)
{
	switch(ID)
	{
	case -1:
		std::cout << "error\n";
		std::cin.ignore();
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
	std::cout << "Critical error in ImageManager, or NULL has passed in getImage\n";
	std::cin.ignore();
	return NULL;
}