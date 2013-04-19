#pragma once
#include "globals.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
class BaseSprite
{
public:
	BaseSprite(void);

	void Init(ALLEGRO_BITMAP *image = NULL, int spriteWidth = 0, int spriteHeight = 0, int imageCount = 0, int frameDelay = 0);

	//get vars
	int GetSpiteWidth()		{return spriteWidth;}
	int GetSpiteHeight()	{return spriteHeight;}
	int GetImageCount()		{return imageCount;}
	int GetImageIndex()		{return imageIndex;}

	//set vars
	void SetFrameDelay(int frameDelay)	{BaseSprite::frameDelay = frameDelay;}
protected:
	int spriteWidth;
	int spriteHeight;
	int imageCount;
	int imageIndex;
	int curImage;

	int frameDelay;
	int frameCount;

	ALLEGRO_BITMAP *image;
};