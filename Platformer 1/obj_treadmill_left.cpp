#include "obj_treadmill_left.h"


obj_Treadmill_Left::obj_Treadmill_Left(void)
{
	//EASTEREGG
	//Reddit is amazing
	SetID(TREADMILL);
	
	boundUp = 0;
	boundDown = 32;
	boundLeft = 0;
	boundRight = 32;

	image = ImageManager::GetInstance().GetImage(11);

	frameCount = 0;
	currentFrame = 0;

	velX = -2;
}


obj_Treadmill_Left::~obj_Treadmill_Left(void)
{
}

void obj_Treadmill_Left::Update()
{
	frameCount+=1;
	if(frameCount > frameDelay)
	{
		currentFrame+=2;
		frameCount = 0;
	}
	while(currentFrame > maxFrame)
		currentFrame -= maxFrame + 1;
}

void obj_Treadmill_Left::Draw()
{
	al_draw_bitmap_region(image, currentFrame*32, 0, 32, 32, x -_camX, y -_camY, 0);
}