#include "Wall.h"


Wall::Wall(void)
{
	boundUp = 0;
	boundDown = 32;
	boundLeft=0;
	boundRight=32;
	SetID(WALL);
	SetDepth(-10);
	SetCollisionType(BB);
	image =  ImageManager::GetInstance().GetImage(ImageManager::IMG_WALL);
	SetAlive(true);
}

void Wall::Draw()
{
	//al_draw_filled_rectangle(x-boundX,y-16,x+boundX,y+16,al_map_rgba(0,255,0,127));
	al_draw_bitmap(image, x-_camX,y-_camY,0);
}
void Wall::Destroy()
{
	GameObject::Destroy();
}