#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
class BaseSprite
{
public:
	BaseSprite(void);

	void init(ALLEGRO_BITMAP *image = NULL, int spriteWidth = 0, int spriteHeight = 0, int imageCount = 0, int frameDelay = 0);

	//get vars
	int getSpiteWidth()		{return spriteWidth;}
	int getSpiteHeight()	{return spriteHeight;}
	int getImageCount()		{return imageCount;}
	int getImageIndex()		{return imageIndex;}

	//set vars
	void setFrameDelay(int frameDelay)	{BaseSprite::frameDelay = frameDelay;}
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