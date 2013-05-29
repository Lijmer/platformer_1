#include "Spike_Up.h"


Spike_Up::Spike_Up(void)
{
	SetDepth(0);
}

void Spike_Up::Init(float x, float y)
{
	StaticObject::Init(x,y);
	xPoint1 = x;
	yPoint1 = y+32;
	xPoint2 = x+32;
	yPoint2 = y+32;
	xPoint3 = x+16;
	yPoint3 = y;
	SetCollisionType(TBB);
	image = ImageManager::GetInstance().GetImage(ImageManager::IMG_SPIKE_UP);
}

void Spike_Up::Draw()
{
	al_draw_bitmap(image,x-_camX,y-_camY,0);
}

void Spike_Up::Destroy()
{

}