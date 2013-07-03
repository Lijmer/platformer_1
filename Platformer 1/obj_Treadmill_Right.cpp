#include "obj_Treadmill_Right.h"


obj_Treadmill_Right::obj_Treadmill_Right(void)
{
	SetID(TREADMILL_RIGHT);
	
	boundUp = 0;
	boundDown = 32;
	boundLeft = 0;
	boundRight = 32;

	image = ImageManager::GetInstance().GetImage(ImageManager::IMG_TREADMILL);

	frameCount = 0;
	currentFrame = 0;
}


obj_Treadmill_Right::~obj_Treadmill_Right(void)
{
}

void obj_Treadmill_Right::Update()
{
	frameCount+=1;
	if(frameCount > frameDelay)
	{
		currentFrame-=1;
		frameCount = 0;
	}
	while(currentFrame < 0)
		currentFrame += maxFrame + 1;
}

void obj_Treadmill_Right::Draw()
{
	al_draw_bitmap_region(image, currentFrame*32, 0, 32, 32, x, y, 0);
}