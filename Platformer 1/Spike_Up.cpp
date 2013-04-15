#include "Spike_Up.h"


Spike_Up::Spike_Up(void)
{
	SetDepth(0);
}

void Spike_Up::Init(float x, float y)
{
	StaticObject::Init(x,y);
	xPoint1 = x+1;
	yPoint1 = y+31;
	xPoint2 = x+31;
	yPoint2 = y+31;
	xPoint3 = x+15;
	yPoint3 = y+1;
	SetCollisionType(TBB);
	image = ImageManager::GetInstance().GetImage(3);
}

void Spike_Up::Draw()
{
	al_draw_bitmap(image,x-_camX,y-_camY,0);
}

void Spike_Up::Destroy()
{

}