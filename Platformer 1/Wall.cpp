#include "Wall.h"


Wall::Wall(void)
{
	boundUp = 0;
	boundDown = 32;
	boundLeft=0;
	boundRight=32;
	setID(WALL);
	setDepth(-10);
	setCollisionType(BB);
	image =  ImageManager::getInstance().getImage(2);
}

void Wall::draw()
{
	//al_draw_filled_rectangle(x-boundX,y-16,x+boundX,y+16,al_map_rgba(0,255,0,127));
	al_draw_bitmap(image, x-_camX,y-_camY,0);
}
void Wall::destroy()
{
	GameObject::destroy();
}