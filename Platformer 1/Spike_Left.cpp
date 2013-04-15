#include "Spike_Left.h"


Spike_Left::Spike_Left(void)
{
	SetDepth(0);
}

void Spike_Left::Init(float x,float y)
{
	StaticObject::Init(x,y);
	xPoint1 = x+1;
	yPoint1 = y+15;
	xPoint2 = x+31;
	yPoint2 = y+1;
	xPoint3 = x+31;
	yPoint3 = y+31;
	SetCollisionType(TBB);
	image = ImageManager::GetInstance().GetImage(5);
}

void Spike_Left::Draw()
{
	al_draw_bitmap(image,x-_camX,y-_camY,0);
}

void Spike_Left::Destroy()
{

}