#include "BaseSprite.h"

BaseSprite::BaseSprite(void)
{
	spriteWidth = 0;
	spriteHeight = 0;
	imageCount = 0;
	imageIndex = 0;
	curImage = 0;

	frameDelay = 0;
	frameCount = 0;

	image = NULL;
}

void BaseSprite::Init(ALLEGRO_BITMAP *image, int spriteWidth, int spriteHeight, int imageCount, int frameDelay)
{
	if(image != NULL)
		BaseSprite::image = image;
	BaseSprite::spriteWidth = spriteWidth;
	BaseSprite::spriteHeight = spriteHeight;
	BaseSprite::imageCount = imageCount;
	imageIndex = 0;
	curImage = 0;
	BaseSprite::frameDelay = frameDelay;
	frameCount = 0;
}