#include "obj_Platform_Vertical.h"
#include "GameObjectManager.h"

obj_Platform_Vertical::obj_Platform_Vertical()
{
	SetID(VERTICAL_PLATFORM);
	isGoingUp = true;
	velY = -2;
	boundUp = 0;
	boundDown = 16;
	boundLeft = 0;
	boundRight = 32;
	image = ImageManager::GetInstance().GetImage(ImageManager::IMG_PLATFORM);
	SetDepth(-50);
	exceptionIDs[0] = WALL_FADE;
	exceptionIDs[1] = SAVE;
	exceptionIDs[2] = HORIZONTAL_PLATFORM;
	exceptionIDs[3] = VERTICAL_PLATFORM;
	exceptionIDsSize = 4;
}


obj_Platform_Vertical::~obj_Platform_Vertical(void)
{
	
}

void obj_Platform_Vertical::Update()
{
	if(isGoingUp)
	{
		if(GameObjectManager::GetInstance().PlaceFree(x, y + velY - 23, boundUp, boundDown, boundLeft, boundRight, GetInstanceID(), exceptionIDs, exceptionIDsSize))
		{
			y+=velY;
		}
		else
		{
			velY=-velY;
			isGoingUp = false;
		}
	}
	if(!isGoingUp)
	{
		if(GameObjectManager::GetInstance().PlaceFree(x, y + velY + 23, boundUp, boundDown, boundLeft-1, boundRight-1, GetInstanceID(), exceptionIDs, exceptionIDsSize))
		{
			y+=velY;
		}
		else
		{
			velY=-velY;
			isGoingUp = true;
		}
	}
}

void obj_Platform_Vertical::Draw()
{
	al_draw_bitmap(image, x-_camX, y-_camY,0);
}

void obj_Platform_Vertical::Destroy()
{}