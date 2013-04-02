#include "BaseSprite.h"


BaseSprite::BaseSprite(void)
{
}

void BaseSprite::init(ALLEGRO_BITMAP *image, int spriteWidth, int spriteHeight, int imageCount, int frameDelay)
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