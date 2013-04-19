#include "obj_Platform_Horizontal.h"


obj_Platform_Horizontal::obj_Platform_Horizontal(bool(*PlaceFree)(float x, float y, int boundUp, int boundDown, int boundLeft, int boundRight, unsigned int instanceID, int *exceptionIDs))
{
	obj_Platform_Horizontal::PlaceFree = PlaceFree;
	image = ImageManager::GetInstance().GetImage(10);
	boundUp = 0;
	boundDown = 16;
	boundLeft = 0;
	boundRight = 32;
	SetID(HORIZONTAL_PLATFORM);

	exceptionIDs[0] = WALL_FADE;
	exceptionIDs[1] = SAVE;
	exceptionIDs[2] = VERTICAL_PLATFORM;
	exceptionIDs[3] = HORIZONTAL_PLATFORM;
	exceptionIDs[4] = PLAYER;
}


obj_Platform_Horizontal::~obj_Platform_Horizontal(void)
{
}

void obj_Platform_Horizontal::Update()
{
	if(PlaceFree(x+velX, y, boundUp, boundDown, boundLeft, boundRight, GetInstanceID(), exceptionIDs))
	{
		x+=velX;
	}
	else
		velX=-velX;
}

void obj_Platform_Horizontal::Draw()
{
	al_draw_bitmap(image, x, y, 0);
}

void obj_Platform_Horizontal::Destroy()
{

}