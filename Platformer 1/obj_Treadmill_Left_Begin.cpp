#include "obj_Treadmill_Left_Begin.h"


obj_Treadmill_Left_Begin::obj_Treadmill_Left_Begin(void)
{
	SetID(TREADMILL_LEFT);
	
	boundUp = 0;
	boundDown = 32;
	boundLeft = 0;
	boundRight = 32;

	//This needs to be changed!
	image = ImageManager::GetInstance().GetImage(11);

	frameCount = 0;
	currentFrame = 0;
}


obj_Treadmill_Left_Begin::~obj_Treadmill_Left_Begin(void)
{

}
