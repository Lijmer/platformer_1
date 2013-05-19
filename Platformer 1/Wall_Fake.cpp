#include "Wall_Fake.h"


Wall_Fake::Wall_Fake(void)
{
	SetID(WALL_FAKE);
	boundUp=0;
	boundDown=0;
	boundLeft=0;
	boundRight=0;
	SetDepth(0);
	SetCollidable(false);
	image = ImageManager::GetInstance().GetImage(ImageManager::IMG_WALL);
}

void Wall_Fake::Draw()
{
	al_draw_bitmap(image,x-_camX,y-_camY,0);
}
void Wall_Fake::Destroy()
{}