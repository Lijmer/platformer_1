#include "obj_Treadmill_Left_End.h"


obj_Treadmill_Left_End::obj_Treadmill_Left_End(void)
{
	SetID(TREADMILL_LEFT);
	
	boundUp = 0;
	boundDown = 32;
	boundLeft = 0;
	boundRight = 32;

	image = ImageManager::GetInstance().GetImage(13);

	frameCount = 0;
	currentFrame = 0;
}


obj_Treadmill_Left_End::~obj_Treadmill_Left_End(void)
{
}
