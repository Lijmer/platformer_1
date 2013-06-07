#include "Background.h"
#include "FileManager.h"
#include "DisplayManager.h"
#include "LevelManager.h"
#include "Transformer.h"
#include <allegro5/allegro_native_dialog.h>

#include "globals.h"

#include <sstream>

using namespace Transformer;

Background::Background(void)
{
	tilt=0;
	tiltSpeed=0;
	velX=0;
	velY=0;
	scaleX=1;
	scaleY=1;
	imageWidth=0;
	imageHeight=0;
	image = NULL;

	cx=0;
	cy=0;
	offsetX=0;
	offsetY=0;
}

Background::~Background(void)
{
	al_destroy_bitmap(canvas);
	DestroyBackground();
}

void Background::Init()
{
	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
	canvas=al_create_bitmap(_SCREEN_WIDTH, _SCREEN_HEIGHT);
}

void Background::LoadBackgroundFromLevel(int level)
{
	LoadBackground(FileManager::GetInstance().LoadBackgroundNum(level));
}
void Background::LoadBackground(int ID)
{
	DestroyBackground();

	switch(ID)
	{
	case -1:
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "Error!",
			"Background", "no backgroundNum or -1 was entered in the level file", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		break;
	case -2:
		image = al_load_bitmap("img/bkg/menu.png");
		SetVelX(-50);
		break;
	case 0:
		image = al_load_bitmap("img/bkg/level1.png");
		break;
	}
	if(image == NULL)
	{
		std::stringstream ss;
		ss << "Couldn't load background with ID: " << ID;
		al_show_native_message_box(DisplayManager::GetInstance().GetDisplay(), "Error!",
			"Background", ss.str().c_str(), NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return;
	}
	imageWidth = al_get_bitmap_width(image);
	imageHeight = al_get_bitmap_height(image);

	al_lock_bitmap(image, al_get_bitmap_format(image), ALLEGRO_LOCK_READONLY);
}
void Background::DestroyBackground()
{
	if(image!=NULL)
	{
		al_destroy_bitmap(image);
		image=NULL;
	}
}

void Background::Update()
{
	if(LevelManager::GetInstance().GetCurrentLevel()==LevelManager::LVL_LEVEL1)
	{
		IncreaseVelXByRandomRange(-.5, .5);
		IncreaseVelYByRandomRange(-.5, .5);
	}
	offsetX+=velX;
	offsetY+=velY;
	tilt+=tiltSpeed;

	while(offsetX>imageWidth)
		offsetX-=imageWidth;
	while(offsetX<0)
		offsetX+=imageWidth;
	while(offsetY>imageHeight)
		offsetY-=imageHeight;
	while(offsetY<0)
		offsetY+=imageHeight;
}

void Background::IncreaseVelXByRandomRange(float min, float max)
{
	float increase = min + float(rand())/((float)RAND_MAX/(max-min));
	velX+=increase;
}
void Background::IncreaseVelYByRandomRange(float min, float max)
{
	float increase = min + float(rand())/((float)RAND_MAX/(max-min));
	velY+=increase;
}

void Background::Draw()
{
	if(image==NULL)
		return;

	al_set_target_bitmap(canvas);
	al_clear_to_color(al_map_rgb(0,0,0));

	int startX=0;
	if(offsetX>0)
		startX=-imageWidth;

	int startY=0;
	if(offsetY>0)
		startY=-imageHeight;

	int widthLeft=_SCREEN_WIDTH%imageWidth;
	int heightLeft=_SCREEN_HEIGHT%imageHeight;


	for(int x=startX; x<_SCREEN_WIDTH+imageWidth; x+=imageWidth)
	{
		for(int y=startY; y<_SCREEN_HEIGHT+imageHeight; y+=imageHeight)
		{
			if((_SCREEN_WIDTH-x)/imageWidth>0 && (_SCREEN_WIDTH-y)/imageHeight>0)
				al_draw_bitmap_region(image, 0,0,imageWidth, imageHeight, x+offsetX, y+offsetY,0);
			else if((_SCREEN_HEIGHT-y)/imageHeight>0)
				al_draw_bitmap_region(image, 0,0,widthLeft, imageHeight, x+offsetX, y+offsetY,0);
			else if((_SCREEN_WIDTH-x)/imageWidth>0)
				al_draw_bitmap_region(image, 0,0,imageWidth, heightLeft, x+offsetX, y+offsetY,0);
			else
				al_draw_bitmap_region(image, 0,0,widthLeft, heightLeft, x+offsetX, y+offsetY,0);
		}
	}
	al_set_target_backbuffer(DisplayManager::GetInstance().GetDisplay());
	al_draw_scaled_bitmap(canvas, 0, 0, _SCREEN_WIDTH, _SCREEN_HEIGHT, TranslateDisplayX(0), TranslateDisplayY(0), ScaleDisplay(_SCREEN_WIDTH), ScaleDisplay(_SCREEN_HEIGHT), 0);
}