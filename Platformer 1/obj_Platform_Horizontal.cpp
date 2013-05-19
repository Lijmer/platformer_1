#include "obj_Platform_Horizontal.h"
#include "GameObjectManager.h"

obj_Platform_Horizontal::obj_Platform_Horizontal()
{
	image = ImageManager::GetInstance().GetImage(ImageManager::IMG_PLATFORM);
	boundUp = 0;
	boundDown = 16;
	boundLeft = 0;
	boundRight = 32;
	SetID(HORIZONTAL_PLATFORM);
	SetDepth(-50);
	exceptionIDs[0] = WALL_FADE;
	exceptionIDs[1] = SAVE;
	exceptionIDs[2] = VERTICAL_PLATFORM;
	exceptionIDs[3] = HORIZONTAL_PLATFORM;
	exceptionIDs[4] = PLAYER;
	exceptionIDsSize = 5;
}

obj_Platform_Horizontal::~obj_Platform_Horizontal(void)
{
}

void obj_Platform_Horizontal::Update()
{
	if(GameObjectManager::GetInstance().PlaceFree(x+velX, y, boundUp-1, boundDown-1, boundLeft, boundRight, GetInstanceID(), exceptionIDs, exceptionIDsSize))
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