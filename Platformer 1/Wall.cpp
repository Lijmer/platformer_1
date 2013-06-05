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

void Wall::Destroy()
{
	GameObject::Destroy();
}